#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "view.h"

View view;

void display ( void ) {
    view.display();
}

void reshape( int w, int h ) {
    view.reshape( w, h );
}

void idle() {
    view.idle();
}

int main( int argc, char **argv ) {    
    view.setMainWindow( argc, argv);
    GLUI_Master.set_glutIdleFunc( idle );
    glutDisplayFunc( display  );
    glutReshapeFunc( reshape );
    view.setupGLUI();
    glutMainLoop();
}