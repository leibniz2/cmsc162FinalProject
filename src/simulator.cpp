#include <GL/gl.h>
#include <GL/glut.h>

#include "simulator.h"
#include "cloth.h"

Cloth cloth ( 14, 10, 45, 50 );
Simulator * ptr_global_instance = NULL;


void Simulator::init() {
  glClearColor(1.000f, 0.894f, 0.710f, 1.000f);
}

void Simulator::display( void ) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-6.5,6,-9.0f); // move camera out and center on the cloth
	glRotatef(25,0,1,0); // rotate a bit to see the cloth from the side
	cloth.draw(); 
	
	glPushMatrix();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if( h == 0 ) {
		gluPerspective( 80, (float) w, 1.0, 5000.0);
	} else {
		gluPerspective( 80, (float) w / (float) h, 1.0, 5000.0);
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

extern "C" void display_callback() {
	ptr_global_instance -> display();
}

extern "C" void reshape_callback() {
	ptr_global_instance -> reshape( int w, int h );
}

void Simulator::setup_display() {
	::ptr_global_instance = this;
	::glutDisplayFunc( ::display_callback );
}

void Simulator::setup_reshape() {
	::ptr_global_instance = this;
	::glutReshapeFunc( ::reshape_callback );
}

