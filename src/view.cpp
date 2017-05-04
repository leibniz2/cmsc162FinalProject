#include "view.h"

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "values.h"
#include "controller.h"
#include "iostream"


static Values* values = Values::Instance();
static Controller* ctr = Controller::Instance();

View::View() {}

void View::drawTriangle( Particle * p1, Particle *p2,
    Particle * p3, const Vec3 color ) {
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

void View::drawObject() {
    if ( ctr -> g_has_cloth_id_val() ) {
        glBegin( GL_TRIANGLES );
        for( int x = 0 ; x < cloth.get_particles_width() - 1; x++ ) {
            for( int y = 0; y < cloth.get_particles_height() - 1; y++ ) {
                Vec3 color( 0, 0, 0 );
                if ( x % 2 ) {
                    color = Vec3( 0.377f, 0.47f, 0.2f );
                } else {
                    color = Vec3( 1.0f, 1.0f, 1.0f );
                }

                drawTriangle( cloth.getParticle( x + 1, y), cloth.getParticle( x, y),
                    cloth.getParticle( x , y + 1 ), color );
                drawTriangle( cloth.getParticle( x + 1, y + 1), cloth.getParticle( x + 1, y ),
                    cloth.getParticle( x, y + 1), color );
            }
        }
        glEnd();
    }
}

void View::setMainWindow( int argc, char ** argv ) {
    glutInit( &argc, argv );
    glutInitWindowSize( 600, 400 );
    glutInitWindowPosition(300, 150 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    main_window = glutCreateWindow( "CMSC 162: Cloth Simulator" );
    init();
}


void View::init() {
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_COLOR_MATERIAL );
    cloth.build( 1, 1, 25, 25 );
}

void View::display( void ) {

    cloth.update_properties();

    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    glTranslatef( ctr -> g_translatexy_id()[0], ctr -> g_translatexy_id()[1] , 0.0f );
    glRotatef( 30.0, 0.0, 1.0, 0.0 );
    drawObject();

    glutSwapBuffers();
    glutPostRedisplay();
}

void View::reshape( int w, int h ){
    window_width = w;
    window_height = h;
    GLUI_Master.get_viewport_area( &vx, &vy, &vw, &vh );
    glViewport( vx, vy, vw, vh );
    glutPostRedisplay();
}


void View::idle() {
    glutSetWindow( main_window );
    glutPostRedisplay();
    Sleep( 50 );
}

void glui_callback( int control_id ) {
    ctr -> callback_fn( control_id );
}

void View::setupGLUI() {
    GLUI * glui_r_swindow = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
    
    // //add the main panel
    GLUI_Panel *main_panel = glui_r_swindow -> add_panel("CONTROL PANEL");

    // this is the subpanel containing customization for environmental factors
    GLUI_Panel *ef_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Environmental Factors");

    GLUI_Listbox *rigidity_item_id = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Cloth Type", ctr -> g_rigidity_item_id() , 0, glui_callback );
    GLUI_Listbox *gravity_item_id = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Gravity", ctr -> g_gravity_item_id() , 1, glui_callback );
    GLUI_Listbox *wind_item_id = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Wind Speed", ctr -> g_wind_item_id() , 2, glui_callback );
    
    rigidity_item_id -> add_item ( 1, "0.75x (Rigid)");
    rigidity_item_id -> add_item ( 2, "0.50x");
    rigidity_item_id -> add_item ( 3, "0.25x");
    rigidity_item_id -> add_item ( 4, "Normal");
    rigidity_item_id -> add_item ( 5, "1.25x");
    rigidity_item_id -> add_item ( 6, "1.50x");
    rigidity_item_id -> add_item ( 7, "2.00x (Soft)");
    rigidity_item_id -> set_int_val (4);

    gravity_item_id -> add_item ( 1, "0.75x (Positive)");
    gravity_item_id -> add_item ( 2, "0.50x");
    gravity_item_id -> add_item ( 3, "0.25x");
    gravity_item_id -> add_item ( 4, "Normal");
    gravity_item_id -> add_item ( 5, "1.25x");
    gravity_item_id -> add_item ( 6, "1.50x");
    gravity_item_id -> add_item ( 7, "2.00x (Negative)");
    gravity_item_id -> add_item ( 8, "None");
    gravity_item_id -> set_int_val (4);

    wind_item_id -> add_item ( 1, "0.75x (Calm)");
    wind_item_id -> add_item ( 2, "0.50x");
    wind_item_id -> add_item ( 3, "0.25x");
    wind_item_id -> add_item ( 4, "Normal");
    wind_item_id -> add_item ( 5, "1.25x");
    wind_item_id -> add_item ( 6, "1.50x");
    wind_item_id -> add_item ( 7, "2.00x (Strong Breeze)");
    wind_item_id -> add_item ( 8, "None");
    wind_item_id -> set_int_val (4);


    GLUI_Panel * obj_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Object Properties");

    GLUI_Listbox *cloth_listbox = glui_r_swindow -> add_listbox_to_panel( obj_panel,
        "Cloth style", ctr -> g_cloth_item_id() , 3, glui_callback );
    GLUI_Listbox *ball_listbox = glui_r_swindow -> add_listbox_to_panel( obj_panel,
        "Ball style", ctr -> g_ball_item_id() , 4, glui_callback );
    
    cloth_listbox -> add_item ( 0, "Solid White (Default)" );
    cloth_listbox -> add_item ( 1, "Solid Green" );
    cloth_listbox -> add_item ( 2, "Checkered B/W" );
    cloth_listbox -> add_item ( 3, "Philippine flag" );
    cloth_listbox -> set_int_val (0);

    ball_listbox -> add_item ( 0, "Solid Black (Default)" );
    ball_listbox -> add_item ( 1, "Solid Red" );
    ball_listbox -> add_item ( 2, "Solid Gray");
    ball_listbox -> set_int_val (0);

    GLUI_Panel * s_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Objects Status");

    glui_r_swindow -> add_checkbox_to_panel ( s_panel, "Show Cloth", ctr -> g_has_cloth_id() );
    glui_r_swindow -> add_checkbox_to_panel ( s_panel, "Show Ball", ctr -> g_has_ball_id() );

    // glui_r_swindow -> add_button ( "Apply" , 4 , glui_callback );
    // glui_r_swindow -> add_button ( "Default" , 5 , glui_callback );

    GLUI_Panel * t_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Controls");
    GLUI_Translation *t_xy = glui_r_swindow -> add_translation_to_panel ( t_panel, 
        "Translation XY", GLUI_TRANSLATION_XY, ctr -> g_translatexy_id() , 5, glui_callback);
    t_xy -> set_speed( 0.001f );
    glui_r_swindow -> set_main_gfx_window ( main_window );
}
