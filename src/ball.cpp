#include "ball.h"
#include "vec3.h"
#include "math.h"

Ball::Ball() { // lol
    center = Vec3(7, -5, 0 );
    radius = 2;
    time_step = 0;
}

void Ball::update_properties() {
    time_step ++ ;
    center.f[2] = cos ( time_step / 50.0 ) * 7;
}

Vec3 Ball::g_center_vector() {
    return center;
}

float Ball::g_radius() {
    return radius;
}