#!/usr/bin/python
# Author: Bryce Schroeder, bryce@lanset.com | AIM4Bryce
# Copyright (c) 2004 Bryce C. E. Schroeder
#
# Permission is hereby granted, free of charge, to any person obtaining a 
# copy of this software and associated files (the "Software"),
# to deal in the Software without restriction, including without limitation 
# the rights to use, copy, modify, merge, publish, distribute, sublicense, 
# and/or sell copies of the Software, and to permit persons to whom the Software 
# is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
_X = 0
_Y = 1

from struct import unpack
import struct

class SLP_Error(Exception):
	"""SLP Parsing error."""
	pass

class SLP_Unimplemented(Exception):
	"""For an unimplemented part of SLP."""
	pass


class SLPShape:
	"""Class representing a SLP shape."""
	file = None
	dataOffset = 0
	myid = 0
	outlineOffset = 0
	paletteOffset = 0
	properties = 0
	size = (0,0) #Width, height
	hotspot = (0,0)
	# The arrays:
	outlines = []
	loffsets = []
	def __init__(self, file, header, myid):
		doff, oloff, paloff, prop, sizex, sizey, hotsx, hotsy = header
		self.file = file
		self.dataOffset = doff
		self.outlineOffset = oloff
		self.paletteOffset = paloff
		self.myid = myid
		self.properties = prop
		self.size = (sizex,sizey) # pair of cords
		self.hotspot = (hotsx,hotsy)
		print "Newshape --------------:"
	def load(self): 
		"""Load everything into the shape."""
		# Seek first the Outline...
		self.file.seek(self.outlineOffset)
		i = 0
		self.outlines = []
		while i < self.size[_Y]:
			self.outlines.append( unpack('<2H',self.file.read(4)) )
			#print self.outlines[i], self.outlines[i][1]-self.outlines[i][0]
			i += 1
		# Seek now the offsets.
		print ">> %X" % self.dataOffset
		self.file.seek(self.dataOffset)
		print "<< %X" % self.file.tell()
		i = 0
		self.loffsets = []
		while i < self.size[_Y]:
			tmp = unpack('<I', self.file.read(4))[0] # Unpack tuple 
			self.loffsets.append(tmp)
			i += 1
		print i, self.size[_Y]
		# Do some error checking:
		if self.paletteOffset != 0:
			raise SLP_Unimplemented, 'Palettes are not implemented in SLPLib.'
			
		#Something is is really messed up, the file offsets are bogus or someting
		#files sizes are coming up < 0 and invalid offsets? maybe look at seek return value
		#Stupid bug: really stupid. Must remember to drink tea if I am going to program
		#after 9:45. ONE character was wrong! ONE! Uck.
	
	def info(self):
		"""Return info about the shape: size, properties, hotspot, etc."""
		return self.properties, self.size, self.hotspot
	
	def rasterize(self, pcolor=1, amXflip=0):
		"""Parse and rasterize an SLP bytestream."""
		map = []
		y = 0
		xsize = self.info()[1][0]
		while y < self.size[_Y]:
			map.append( self.rastLine(self.loffsets[y], self.outlines[y][0], xsize, myY=y, pcolor=pcolor, xflip=amXflip) )
			y += 1
		return map
		
	def skip(self, width, init):
		t = []
		x = 0
		while x < width:
			t.append(init)
			x += 1
		return t
	
	def read(self, lens, apply=None):
		if lens > 1:
			data = self.file.read(lens)
			t = []
			for char in data:
				t.append(char)
			if apply != None:
				le = len(t)
				i = 0
				while i < le:
					t[i] = chr(ord(t[i]) | apply)
					i += 1
			return t
		else:
			return self.file.read(lens)

	def rastLine(self, offset, xstart, xsize, xflip=0, fill=None, scolor1='P-C', scolor2='S-D', pcolor=0x3, myY=0):
		"""Render a line."""
		# Diagnostic print statement.
		print """
		------------- BEGINING LINE %d, @ 0x%06X: --------------
		""" % (myY, offset)
		done = 0
		skip = 0
		print "Skipping ahead %d pixels." % xstart
		rline = self.skip(xstart, fill) # put the blank space in front.
		line = [] # line is the temporary buffer, rline is what will be actualy returned.
		ittr = 0
		self.file.seek(offset)
		first_shadow = 0
		while not done:
			ittr += 1
			#print "                						@0x%06X" % (self.file.tell())
			data = self.file.read(1)
			cmd = ord(data) & 0xF # The command is the low nybble
			
			# Python needs a 'case' statement.
			if cmd == 0 or cmd == 4 or cmd == 8 or cmd == 0xC: #lesser block copy
				length = ord(data) >> 2
				line.extend(self.read(length)) # read is a function that returns a list of bytes from self.file
				print "[%d on %d] | Lesser Block Copy  -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 1 or cmd == 5 or cmd == 9 or cmd == 0xD: #lesser skip
				length = (ord(data) & 0xFC) >> 2
				line.extend(self.skip(length, fill))
				print "[%d on %d] | Lesser Skip        -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 2: # greater block copy
				length = ((ord(data) & 0xF0) << 4) + ord(self.read(1))
				line.extend(self.read(length))
				print "[%d on %d] | Greater Block Copy -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 3: # greater skip
				length = ((ord(data) & 0xF0) << 4) + ord(self.read(1))
				line.extend(self.skip(length, fill))
				print "[%d on %d] | Greater Skip       -> Length: %d, Data: 0x%X NB: " % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 6: # Copy and Transform block
				dat = (ord(data) & 0xF0) >> 4
				if dat == 0:
					length = ord(self.read(1))
				else:
					length = dat
				line.extend(self.read(length, apply=pcolor))
				# no longer uses lambda because it was a waste of time in this instance.
				print "[%d on %d] | Copy & Trans Block -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 7: # Run of plain color
				dat = (ord(data) & 0xF0) >> 4 # high nybble
				if dat == 0:
					length = ord(self.read(1)) # S SECTION HAS BEEN MODIFED. A PROBLEM HERE?
				else:
					length = dat
				line.extend( self.skip(length, self.read(1)) ) # self.skip: also useful for filling.
				print "[%d on %d] | Plain Color Run    -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 0xA: # Transform block
				dat = (ord(data) & 0xF0) >> 4
				if dat == 0:
					length = ord(self.read(1))
				else:
					length = dat
				line.extend( self.skip(length, chr(ord(self.read(1)) | pcolor) ) ) # should be |
				print "[%d on %d] | Player Color Run    -> Length: %d, Data: 0x%X" % (ittr, len(line)+xstart, length, ord(data))
				#-------------------------------------------------------------------------------------------------------
			elif cmd == 0x0B: # Shadow pixels
				# Remove this if statement to improve performance, if you want.
				if first_shadow == 0:
					print SLPErrorReport % ( "Line Rasterizer", 
						"Unknown", self.file.tell(),
						self.myid, myY, len(line) , xsize,
						ittr,
						"WARNING: The 0x0B Shadow Pixels opcode is presently incomplete.",
						ord(data), 'elif cmd == 0x0B:' )
					first_shadow = 1
				else:
					print "Another call to the shadow opcode, on line %d this time..." % myY
				# ---------
				dat = (ord(data) & 0xF0) >> 4
				if dat == 0:
					length = ord(self.read(1))
				else:
					length = dat
				line.extend( self.skip(length, 'SH'))
				
			elif cmd == 0x0E: #Extended commands...
				ex = ord(data)
				if ex == 0x0E: # Render hint
					if xflip:
						skip = 1
						continue
					print "[%d on %d] | Extended Command -> Render Hint -> 0x%X" % (ittr, len(line)+xstart, ord(data))
				elif ex == 0x1E: # also a render hint
					if not xflip:
						skip = 1 #maybe use continue?
						continue
					print "[%d on %d] | Extended Command -> Render Hint -> 0x%X" % (ittr, len(line)+xstart, ord(data))
				elif ex == 0x2E:
					print SLPErrorReport % ( "Line Rasterizer", 
						"Unknown", self.file.tell(),
						self.myid, myY, len(line), xsize,
						ittr,
						"The Extended RLE command Set Transform Color Table 0x2E isn't implemented.",
						ord(data), 'elif ex == 0x2E' )
						
					#raise SLP_Unimplemented, 'Transform color tables unimplemented'
				elif ex == 0x3E:
					print SLPErrorReport % ( "Line Rasterizer", 
						"Unknown", self.file.tell(),
						self.myid, myY, len(line), xsize,
						ittr,
						"The Extended RLE command Set Alternate Transform Color Table 0x3E isn't implemented.",
						ord(data), 'elif ex == 0x3E' )
					#raise SLP_Unimplemented, 'Alternate transform color tables unimplemented.'
				elif ex == 0x4E: # draw special color
					line.append(scolor1)
					print "[%d on %d] | Extended Command -> Draw 1st Special Color -> 0x%X" % (ittr, len(line)+xstart, ord(data))
				elif ex == 0x6E:
					line.append(scolor2)
					print "[%d on %d] | Extended Command -> Draw 2nd Special Color -> 0x%X" % (ittr, len(line)+xstart, ord(data))
				elif ex == 0x5E: # special color run
					line.extend( self.skip(ord(self.read(1)), scolor1) )
					print "[%d on %d] | Extended Command -> 1st Special Color Run" % (ittr, len(line)+xstart)
				elif ex == 0x7E:
					line.extend( self.skip(ord(self.read(1)), scolor2) )
					print "[%d on %d] | Extended Command -> 2nd Special Color Run" % (ittr, len(line)+xstart)
				else:
					print SLPErrorReport % ( "Line Rasterizer", 
						"Unknown", self.file.tell(),
						self.myid, myY, len(line), xsize,
						ittr, 
						"Unknown Extended RLE Command 0x%X" % ex,
						ord(data), 'else:' )
					#raise SLP_Unimplemented, 'Unknown Extended RLE command: 0x%X' % ord(data)
			elif cmd == 0x0F:
				done = 1
				print "[%d of %d]: END OF LINE." % (ittr, len(line)+xstart)
			if skip == 0:
				rline.extend(line)
			else:
				skip = 0
			line = []
		
		rline.extend( self.skip(xsize - len(rline),fill) )
		# diagnostic print
		print """
		--------------- OK DONE ---------------
		"""
		return rline		

				



class SLP:
	"""Object for a whole SLP file."""
	version = ''
	numShapes = 0
	comment = ''
	shapes = []
	file = None
	#data = [] # actual file data, ready for random access :)
	def __init__(self, path):
		self.file = open(path,'r')
	
	def load(self):
		"""Load Everything. Could take a while ;)"""
		try:
			( self.version, self.numShapes, self.comment) = unpack('<4sl24s',self.file.read(32))
			i = 0
			while i < self.numShapes:
				self.shapes.append(SLPShape(self.file, unpack('<4I4i',self.file.read(32)), i ))
				t = self.file.tell()
				self.shapes[i].load()
				self.file.seek(t) #shape.load hyjacks the file so this is needed.
				i += 1
		except struct.error:
			raise SLP_Error, "Bad SLP File."
			
		
	
	def gline(self, shape, line):
		"""Get the data for a line."""
		return self.shapes[shape].data(line)
	
	def gshape(self, shape):
		"""Return the array of lines for a given shape."""
		return self.shapes[shape].lines
	
	def gimage(self, shape):
		"""Return a bitmap."""
		return self.shapes[shape].rasterize()
	
	def gshapeinfo(self, shape):
		"""Return information about a given shape."""
		return self.shapes[shape].info()

def SLPHexStr(string):
	tmp = ''
	for char in string:
		tmp += "%02X." % ord(char)
	return tmp

SLPErrorReport = """
---> THIS IS AN SLP PARSING ERROR/WARNING REPORT! <---
From: "%s"
File: %s	File Position: 0x%06X
Shape: %d	Line (Y): %d	Pixel (X): %d of %d
Interation %d of parsing loop had an error:
: %s
INFO:
Parser was processing the byte: %02X
When it encountered this issue. The code was in '%s'.
---> END REPORT ON ERROR/WARNING <---
"""
