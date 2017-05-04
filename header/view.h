#ifndef _VIEW_
#define _VIEW_

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "cloth.h"
#include "particle.h" // remove this soon
#include "vec3.h" // remove this too


class View {

    private:
        GLuint main_window;
        Cloth cloth;
        int window_width;
        int window_height;
        int vx;
        int vy;
        int vw;
        int vh;

        void drawObject();
        void drawTriangle( Particle *p1, Particle * p2, 
            Particle * p3, const Vec3 color );

    public:
        View();
        void init();
        void idle();
        void setupGLUI();
        void setMainWindow( int argc, char ** argv );
        void display( void );
        void reshape( int w, int h );
};

#endif