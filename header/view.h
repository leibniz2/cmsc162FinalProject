#ifndef _VIEW_
#define _VIEW_

#include <GL/glui.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "cloth.h"
#include "ball.h"
#include "particle.h" 
#include "vec3.h"


class View {

    private:
        GLuint main_window;
        Cloth cloth;
        Ball ball;
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
        void states();
        Vec3 setStyles( int x , int y);
        void reshape( int w, int h );
};

#endif