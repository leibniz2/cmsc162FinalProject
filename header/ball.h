#ifndef _BALL_
#define _BALL_

#include "vec3.h"

class Ball {
    private:
        float radius;
        float time_step;

    public:
        Ball();
        Vec3 center;
        void update_properties();
        Vec3 g_center_vector();
        float g_radius();
};

#endif