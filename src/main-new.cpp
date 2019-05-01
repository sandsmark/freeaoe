// OpenGL/GLFW Basecode | r3dux

#include <iostream>
#include <GL/glfw.h> // Include OpenGL Framework library
using namespace std;

void initGL(int width, int height)
{
    // ----- Window and Projection Settings -----

    // Set the window title
    glfwSetWindowTitle("GLFW Basecode");

    // Setup our viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Change to the projection matrix, reset the matrix and set up orthagonal projection (i.e. 2D)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1); // Paramters: left, right, bottom, top, near, far

    // ----- OpenGL settings -----

    glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)

    glEnable(GL_SMOOTH);		// Enable (gouraud) shading

    glDisable(GL_DEPTH_TEST); 	// Disable depth testing

    glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(5.0f);		// Set a 'chunky' line width

    glEnable(GL_LINE_SMOOTH);	// Enable anti-aliasing on lines

    glPointSize(5.0f);		// Set a 'chunky' point size

    glEnable(GL_POINT_SMOOTH);	// Enable anti-aliasing on points
}

void drawScene()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ----- Draw stuff! -----

    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2f(0.0f, 0.0f);

    glColor3ub(0, 0, 255);
    glVertex2f(800.0f, 600.0f);
    glEnd();

    // ----- Stop Drawing Stuff! ------

    glfwSwapBuffers(); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
}

int main()
{
    // Frame counter and window settings variables
    int frame      = 0, width     = 800, height      = 600;
    int redBits    = 8, greenBits = 8,   blueBits    = 8;
    int alphaBits  = 8, depthBits = 0,   stencilBits = 0;

    // Flag to keep our main loop running
    bool running = true;

    // Initialise glfw
    glfwInit();

    // Create a window
    if(!glfwOpenWindow(width, height, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, GLFW_WINDOW))
    {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }

    // Call our initGL function to set up our OpenGL options
    initGL(width, height);

    while (running == true)
    {
        // Increase our frame counter
        frame++;

        // Draw our scene
        drawScene();

        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
    }

    glfwTerminate();

    return 0;
}
