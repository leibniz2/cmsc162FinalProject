#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "view.h"
#include "controller.h"

static Controller* ctr = Controller::Instance();

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

void keyboard ( unsigned char key, int x, int y) {
    ctr -> keyboard( key, x, y );
}

void special( int key, int x, int y ){
    ctr -> special( key, x, y );
}

int main( int argc, char **argv ) {    
    view.setMainWindow( argc, argv);
    GLUI_Master.set_glutIdleFunc( idle );
    glutDisplayFunc( display  );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special );
    view.setupGLUI();
    glutMainLoop();
}