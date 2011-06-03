#include "structs.h"

// For NULL:
#include <stdlib.h>

genie_civ::genie_civ()
{
  unknown04 = NULL;
}
genie_civ::~genie_civ()
{
  delete[] unknown04;
}


genie_unit::genie_unit()
{
  unknown01 = NULL;
  name1 = NULL;
  name2 = NULL;

  part2 = NULL;
  part3 = NULL;
  part4 = NULL;
  part5 = NULL;
  part6 = NULL;
  part7 = NULL;
  part8 = NULL;
  part9 = NULL;
  part10 = NULL;
  part11 = NULL;
  part12 = NULL;
  part14 = NULL;
  part15 = NULL;

  attacks = NULL;
  armour = NULL;
}

genie_unit::~genie_unit()
{
  // I like garbage collection.

  delete[] unknown01;
  delete[] name1;
  delete[] name2;

  delete[] part2;
  delete[] part3;
  delete[] part4;
  delete[] part5;
  delete[] part6;
  delete[] part7;
  delete[] part8;
  delete[] part9;
  delete[] part10;
  delete[] part11;
  delete[] part12;
  delete[] part14;
  delete[] part15;

  delete[] attacks;
  delete[] armour;
}



// Automatically do sizeof type rubbish
//#define brds(i) DataBuffer->read(&##i, sizeof(i))


// and allocate it too
//#define brdm(i, t) i = new t; DataBuffer->read(i, sizeof(t))
// and handle multiple small types
//#define brdl(i, s, t) i = new t[s]; DataBuffer->read(i, s*sizeof(t))


void genie_unit::Read ( Buffer *DataBuffer, int VersionNum )
{
  
  
  brds ( type );

  brds ( head );

  brds ( unknown01_length );
  if ( unknown01_length < 0 )
    throw "Unrecognised .dat format";

  brdl <raw> ( unknown01, 5*unknown01_length);

  brds ( sounds );

  if ( head.name1_length )
  {
    brdl <char> ( name1, head.name1_length);
  }
  else
  {
    name1 = new char[1];
    name1[0] = 0;
  }

  if ( VersionNum == 59 )
  {
    brds ( name2_length );
    if ( name2_length )
    {
      brdl <char> ( name2, name2_length);
    }
    else
    {
      name2 = new char[1];
      name2[0] = 0;
    }

    brds ( unitline_id );
    brds ( mintechlevel );
  }
  brds ( id2 );
  brds ( id3 );

  if ( type != 10 )
  {
    brdm <genie_unit_part2> ( part2 );
  }

  switch ( type )
  {
    case 30:
      brdm <genie_unit_part4>( part4 );
      break;
    case 60:
      brdm <genie_unit_part6>( part6 );
      brdm <genie_unit_part5> ( part5 );
      brds ( attacks_length );
      brdl <short> ( attacks, 2*attacks_length );
      brds ( armour_length );
      brdl <short> ( armour, 2*armour_length );
      brdm <genie_unit_part9> ( part9 );
      break;
    case 70:
      brdm <genie_unit_part3> ( part3 );
      brdm <genie_unit_part5> ( part5 );
      brds ( attacks_length );
      brdl <short> ( attacks, 2*attacks_length );
      brds ( armour_length );
      brdl <short> ( armour, 2*armour_length );
      brdm <genie_unit_part7> ( part7 );
      brdm <genie_unit_part10> ( part10 );
      brdm <genie_unit_part12> ( part12 );
      brdm <genie_unit_part14> ( part14 );
      break;
    case 80:
      brdm <genie_unit_part3> ( part3 );
      brdm <genie_unit_part5> ( part5 );
      brds ( attacks_length );
      brdl <short> ( attacks, 2*attacks_length );
      brds ( armour_length );
      brdl <short> ( armour, 2*armour_length );
      brdm <genie_unit_part8> ( part8 );
      brdm <genie_unit_part11> ( part11 );
      brdm <genie_unit_part12> ( part12 );
      brdm <genie_unit_part15> ( part15 );
      break;
  }
}

// Equivalent things for writing
/*#define bwrs(i) DataBuffer->write(&##i, sizeof(i))
#define bwrm(i, t) DataBuffer->write(i, sizeof(t))
#define bwrl(i, s, t) DataBuffer->write(i, s*sizeof(t))
*/

// Code duplication is bad. There must be a nicer way to do this...

void genie_unit::Write ( Buffer *DataBuffer, int VersionNum )
{
  bwrs ( type );

  bwrs ( head );

  bwrs ( unknown01_length );
  bwrl <raw> ( unknown01, 5*unknown01_length );

  bwrs ( sounds );

  if ( head.name1_length )
  {
    bwrl <char> ( name1, head.name1_length);
  }

  if ( VersionNum == 59 )
  {
    bwrs ( name2_length );
    if ( name2_length )
    {
      bwrl <char> ( name2, name2_length );
    }

    bwrs ( unitline_id );
    bwrs ( mintechlevel );
  }

  bwrs ( id2 );
  bwrs ( id3 );

  if ( type != 10 )
  {
    bwrm <genie_unit_part2> ( part2 );
  }

  switch ( type )
  {
    case 30:
      bwrm <genie_unit_part4> ( part4 );
      break;
    case 60:
      bwrm <genie_unit_part6> ( part6 );
      bwrm <genie_unit_part5> ( part5 );
      bwrs ( attacks_length );
      bwrl <short> ( attacks, 2*attacks_length );
      bwrs ( armour_length );
      bwrl <short> ( armour, 2*armour_length );
      bwrm <genie_unit_part9> ( part9 );
      break;
    case 70:
      bwrm <genie_unit_part3> ( part3 );
      bwrm <genie_unit_part5> ( part5 );
      bwrs ( attacks_length );
      bwrl <short> ( attacks, 2*attacks_length );
      bwrs ( armour_length );
      bwrl <short> ( armour, 2*armour_length );
      bwrm <genie_unit_part7> ( part7 );
      bwrm <genie_unit_part10> ( part10 );
      bwrm <genie_unit_part12> ( part12 );
      bwrm <genie_unit_part14> ( part14 );
      break;
    case 80:
      bwrm <genie_unit_part3> ( part3 );
      bwrm <genie_unit_part5> ( part5 );
      bwrs ( attacks_length );
      bwrl <short> ( attacks, 2*attacks_length );
      bwrs ( armour_length );
      bwrl <short> ( armour, 2*armour_length );
      bwrm <genie_unit_part8> ( part8 );
      bwrm <genie_unit_part11> ( part11 );
      bwrm <genie_unit_part12> ( part12 );
      bwrm <genie_unit_part15> ( part15 );
      break;
  }
}
