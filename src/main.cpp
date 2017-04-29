#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <math.h>
#include <vector>
#include <iostream>

#include "vec3.h"
#include "particle.h"
#include "constraint.h"
#include "cloth.h"
#include "controller.h"

// window dimension
int window_width = 600;
int window_height = 400;

// window position
int window_x ;
int window_y ;

// represents the drawing are of x, y, width, and height
int vx, vy, vw, vh;

const char *window_title = "CMSC 126: Cloth Simulator";

//windows
GLuint main_window;
GLUI * glui_r_swindow; //subwindows

// LIVE VARIABLES
int has_gravity = 1; // related to 'Gravity' checkbox;
int has_wind = 1; // related to 'Wind' checkbox;
int damping_item_id = 0;
int velocity_item_id = 0;
int cloth_item_id = 0;
int ball_item_id = 0;

Cloth cloth1 ( 2, 1, 25, 40 );


/*****************************************
 *       USER INTERFACE RELATED CODE     *
 *****************************************/

// setup glui window and components
void setupGLUI ();
// setup idle callback
void idle ();
// setup callback related to gui
void glui_callback (int arg );

// support functions
void centerOnScreen();
void drawObject ();

// set OpenGL initial state
void init() {
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    // glClearDepth( 1.0f );
    // glEnable( GL_DEPTH_TEST );
    glDepthFunc ( GL_LEQUAL );
    glEnable ( GL_COLOR_MATERIAL );
    // glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void centerOnScreen (){
    window_x = ( glutGet (GLUT_SCREEN_WIDTH) - window_width) / 2;
    window_x = ( glutGet (GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

void display(void) {
   
    cloth1.update_properties(); // updates particle constraints of the cloth

    glClear ( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    glTranslatef(-1.20f,0.70f,0.0f); // move camera out and center on the cloth
	glRotatef(25,0,1,0); // rotate a bit to see the cloth from the side
    drawObject();

    glutSwapBuffers();
    glutPostRedisplay();
}

void drawTriangle( Particle *p1, Particle * p2, Particle * p3, const Vec3 color ){
        glColor3fv ( (GLfloat*) &color );

        Particle pp1 = ( p1 -> getNormal().normalized() );
        Particle pp2 = ( p2 -> getNormal().normalized() );
        Particle pp3 = ( p3 -> getNormal().normalized() );

        glNormal3fv((GLfloat *) &pp1);
        glVertex3fv((GLfloat *) &(p1->getPos() ));

        glNormal3fv((GLfloat *) &pp2);
        glVertex3fv((GLfloat *) &(p2->getPos() ));

        glNormal3fv((GLfloat *) &pp3);
        glVertex3fv((GLfloat *) &(p3->getPos() ));
}

void drawObject() {
    printf( "Displaying object...\n " );
    // display cloth
    glBegin(GL_TRIANGLES);
        for(int x = 0; x<cloth1.get_particles_width()-1; x++) {
            for(int y=0; y<cloth1.get_particles_height()-1; y++) {
                Vec3 color(0,0,0);
                if (x%2) // red and white color is interleaved according to which column number
                    color = Vec3(0.6f,0.2f,0.2f);
                else
                    color = Vec3(1.0f,1.0f,1.0f);

                drawTriangle(cloth1.getParticle(x+1,y),cloth1.getParticle(x,y),
                    cloth1.getParticle(x,y+1),color);
                drawTriangle(cloth1.getParticle(x+1,y+1), cloth1.getParticle(x+1,y),
                    cloth1.getParticle(x,y+1),color);
            }
        }
    glEnd();  
}

void reshape( int w, int h ) {
    window_width = w;
    window_height = h;

    // get the drawing are viewport characteristics
    GLUI_Master.get_viewport_area ( &vx, &vy, &vw, &vh );

    // set the viewport
    glViewport ( vx, vy, vw, vh );

    // call post redisplay to redraw contents
    glutPostRedisplay();
}

void setupGLUI () {
    // set idle function
    GLUI_Master.set_glutIdleFunc ( idle );

    // create GLUI window
    glui_r_swindow = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
    //add the main panel
    GLUI_Panel *main_panel = glui_r_swindow -> add_panel("CONTROL PANEL");

    // this is the subpanel containing customization for environmental factors
    GLUI_Panel *ef_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Environmental Factors");

    GLUI_Listbox *damping_listbox = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Damping", &damping_item_id, 0, glui_callback );
    GLUI_Listbox *velocity_listbox = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Velocity", &velocity_item_id, 1, glui_callback );
    
    damping_listbox -> add_item ( 1, "0.75x");
    damping_listbox -> add_item ( 2, "0.50x");
    damping_listbox -> add_item ( 3, "0.25x");
    damping_listbox -> add_item ( 4, "Normal");
    damping_listbox -> add_item ( 5, "1.25x");
    damping_listbox -> add_item ( 6, "1.50x");
    damping_listbox -> add_item ( 7, "2.00x");
    damping_listbox -> set_int_val (4);

    velocity_listbox -> add_item ( 1, "0.75x");
    velocity_listbox -> add_item ( 2, "0.50x");
    velocity_listbox -> add_item ( 3, "0.25x");
    velocity_listbox -> add_item ( 4, "Normal");
    velocity_listbox -> add_item ( 5, "1.25x");
    velocity_listbox -> add_item ( 6, "1.50x");
    velocity_listbox -> add_item ( 7, "2.00x");
    velocity_listbox -> set_int_val (4);

    glui_r_swindow -> add_separator_to_panel ( ef_panel );

    glui_r_swindow -> add_checkbox_to_panel ( ef_panel, "Gravity", &has_gravity);
    glui_r_swindow -> add_checkbox_to_panel ( ef_panel, "Wind", &has_wind);

    GLUI_Panel * obj_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Object Properties");

    GLUI_Listbox *cloth_listbox = glui_r_swindow -> add_listbox_to_panel( obj_panel,
        "Cloth color", &cloth_item_id, 2, glui_callback );
    GLUI_Listbox *ball_listbox = glui_r_swindow -> add_listbox_to_panel( obj_panel,
        "Ball color", &ball_item_id, 3, glui_callback );
    
    cloth_listbox -> add_item ( 0, "Solid White (Default)" );
    cloth_listbox -> add_item ( 1, "Solid Green" );
    cloth_listbox -> add_item ( 2, "Checkered B/W" );
    cloth_listbox -> add_item ( 3, "Philippine flag" );
    cloth_listbox -> set_int_val (0);

    ball_listbox -> add_item ( 0, "Solid Black (Default)" );
    ball_listbox -> add_item ( 1, "Solid Red" );
    ball_listbox -> set_int_val (0);

    glui_r_swindow -> add_button ( "Apply" , 4 , glui_callback );
    glui_r_swindow -> add_button ( "Default" , 5 , glui_callback );

    glui_r_swindow -> set_main_gfx_window ( main_window );

}

void glui_callback ( int control_id ) {
    Controller().callback_fn(control_id);
}

void idle () {
    glutSetWindow ( main_window );
    glutPostRedisplay ();
    Sleep (50);
}

int main( int argc, char **argv ) {
    centerOnScreen ();
    glutInit( &argc, argv );
    glutInitWindowSize( window_width, window_height );
    glutInitWindowPosition( window_x, window_y );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    main_window = glutCreateWindow( window_title );

    init();

    glutDisplayFunc( display );
    glutReshapeFunc ( reshape );
    setupGLUI();
    glutMainLoop();
}