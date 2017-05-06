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
                Vec3 color = setStyles( x , y );
                drawTriangle( cloth.getParticle( x + 1, y), cloth.getParticle( x, y),
                    cloth.getParticle( x , y + 1 ), color );
                drawTriangle( cloth.getParticle( x + 1, y + 1), cloth.getParticle( x + 1, y ),
                    cloth.getParticle( x, y + 1), color );
            }
        }
        glEnd();
    }
}

Vec3 View::setStyles( int x, int y ) {
    if ( ctr -> g_cloth_item_id_val() == 0 ) {
         if ( x % 2 ) {
            return Vec3( 0.377f, 0.47f, 0.2f ); // military green
        } else {
            return Vec3( 1.0f, 1.0f, 1.0f );
        }  
    } else if ( ctr -> g_cloth_item_id_val() == 1 ) {
        if ( y % 3 ) {
            return Vec3( 0.377f, 0.47f, 0.2f ); // military green
        } else {
            return Vec3( 1.0f, 1.0f, 1.0f );
        }  
    } else {
        return Vec3( 0.377f, 0.47f, 0.2f );
    }
}

void View::setMainWindow( int argc, char ** argv ) {
    glutInit( &argc, argv );
    glutInitWindowSize( 720 , 420 );
    glutInitWindowPosition(240, 360 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    main_window = glutCreateWindow( "CMSC 162: Cloth Simulator" );
    init();
}


void View::init() {
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_COLOR_MATERIAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[4] = {-1.0,1.0,0.5,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos);

	glEnable(GL_LIGHT1);

	GLfloat lightAmbient1[4] = {0.0,0.0,0.0,0.0};
	GLfloat lightPos1[4] = {1.0,0.0,-0.2,0.0};
	GLfloat lightDiffuse1[4] = {0.5,0.5,0.3,0.0};

	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    cloth.build( 10, 10, 35, 45 );
}

void View::states() {
    if( ctr -> g_has_ball_id_val() &&
        ctr -> g_has_cloth_id_val() ) {
         ball.update_properties();
         cloth.update_properties();
         cloth.ball_collision( ball.g_center_vector(), ball.g_radius() );     
    } else if ( ctr -> g_has_ball_id_val() &&
        !ctr -> g_has_cloth_id_val() ) {
          ball.update_properties();
    } else if  ( !ctr -> g_has_ball_id_val() &&
        ctr -> g_has_cloth_id_val() ) {
          cloth.update_properties();  
    } else {
        // if 0,0 , do nothing..
    }
}

void View::display( void ) {
    states();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
	glColor3f(0.741f, 0.718f, 0.420f);
	glVertex3f(-200.0f,-100.0f,-100.0f);
	glVertex3f(200.0f,-100.0f,-100.0f);
    glColor3f(0.933f, 0.910f, 0.667f);
	glVertex3f(200.0f,100.0f,-100.0f);
	glVertex3f(-200.0f,100.0f,-100.0f);
	glEnd();
    glEnable(GL_LIGHTING);
    // glMultMatrixf( ctr -> g_rotation_id() );
    glTranslatef( 
        ctr -> g_translatexy_id()[0], 
        ctr -> g_translatexy_id()[1],
         -9.0f );
    glRotatef( 25.0, 0.0, 1.0, 0.0 );
    drawObject();
    glPushMatrix();
    // printf("%f\n", ball_pos.f[2] );

    glTranslatef( 
        ball.g_center_vector().f[0],
        ball.g_center_vector().f[1],
        ball.g_center_vector().f[2] );
    glColor3f( 0.9f, 0.8f, 0.5f );
    if ( ctr -> g_has_ball_id_val() ) {
        glutSolidSphere( ball.g_radius() - 0.1 , 50, 50 );
    } 
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void View::reshape( int w, int h ){
    glViewport( 0, 0, w, h );
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    if ( h == 0 ) {
        gluPerspective( 80, (float)w, 1.0, 5000.0 );
    } else {
        gluPerspective( 80, (float) w / (float) h, 1.0, 5000.0);
    }
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    glutReshapeWindow( 720, 420 ); // haha. you cannot resize window
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
        "Cloth Type    ", ctr -> g_rigidity_item_id() , 0, glui_callback );
    // glui_r_swindow->add_row_to_panel (ef_panel, false);
    GLUI_Listbox *gravity_item_id = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Gravity         ", ctr -> g_gravity_item_id() , 1, glui_callback );
    GLUI_Listbox *wind_item_id = glui_r_swindow -> add_listbox_to_panel( ef_panel,
        "Wind Speed  ", ctr -> g_wind_item_id() , 2, glui_callback );
    
    rigidity_item_id -> add_item ( 1, "0.75x (Rigid)      ");
    rigidity_item_id -> add_item ( 2, "0.50x");
    rigidity_item_id -> add_item ( 3, "0.25x");
    rigidity_item_id -> add_item ( 4, "Normal");
    rigidity_item_id -> add_item ( 5, "1.25x");
    rigidity_item_id -> add_item ( 6, "1.50x");
    rigidity_item_id -> add_item ( 7, "2.00x (Soft)     ");
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

    wind_item_id -> add_item ( 1, "0.75x (Calm)      ");
    wind_item_id -> add_item ( 2, "0.50x");
    wind_item_id -> add_item ( 3, "0.25x");
    wind_item_id -> add_item ( 4, "Normal");
    wind_item_id -> add_item ( 5, "1.25x");
    wind_item_id -> add_item ( 6, "1.50x");
    wind_item_id -> add_item ( 7, "2.00x (Strong) ");
    wind_item_id -> add_item ( 8, "None");
    wind_item_id -> set_int_val (4);


    GLUI_Panel * obj_panel = glui_r_swindow -> add_panel_to_panel( main_panel, "Object Properties");

    GLUI_Listbox *cloth_listbox = glui_r_swindow -> add_listbox_to_panel( obj_panel,
        "Cloth style     ", ctr -> g_cloth_item_id() , 3, glui_callback );
    
    cloth_listbox -> add_item ( 0, "Checkered (V)  " );
    cloth_listbox -> add_item ( 1, "Default" );
    cloth_listbox -> add_item ( 2, "Solid" );
    cloth_listbox -> set_int_val (1);

    glui_r_swindow -> add_checkbox_to_panel ( obj_panel, "Show Cloth", ctr -> g_has_cloth_id() );
    glui_r_swindow -> add_checkbox_to_panel ( obj_panel, "Show Ball", ctr -> g_has_ball_id() );
    // glui_r_swindow -> add_rotation_to_panel ( obj_panel, "Rotation", ctr -> g_rotation_id(), 4, glui_callback);

    GLUI_Panel * ins_panel = glui_r_swindow -> add_panel( "Keyboard Controls", 1);

    glui_r_swindow -> add_statictext_to_panel(ins_panel, " [UP] to translate along (+) Y-axis");
    glui_r_swindow -> add_statictext_to_panel(ins_panel, " [DOWN] to translate along (-) Y-axis");
    glui_r_swindow -> add_statictext_to_panel(ins_panel, " [LEFT] to translate along (-) X-axis");
    glui_r_swindow -> add_statictext_to_panel(ins_panel, " [RIGHT] to translate along (+) X-axis");
    glui_r_swindow -> add_statictext_to_panel(ins_panel, " [R] to reset translation");

    glui_r_swindow -> set_main_gfx_window ( main_window );
}
