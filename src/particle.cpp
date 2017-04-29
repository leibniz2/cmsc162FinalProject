#include "particle.h"
#include "vec3.h"
#include "values.h"

Particle::Particle( Vec3 p ) {
    pos = p;
    old_pos = p;
    acceleration = ( Vec3(0, 0, 0) );
    mass = 1;
    movable = true;
    accumulated_normal = ( Vec3(0 ,0 ,0) );
}

void Particle::addForce( Vec3 f ) {
    acceleration = acceleration + f / mass;
}

void Particle::timeStep() {
    if ( movable ) {
        Vec3 temp = pos;
        pos = pos + ( pos - old_pos ) * ( 1.0 - DAMPING ) 
            + acceleration * STEP_SIZE;
        old_pos = temp;
        acceleration = Vec3( 0, 0, 0 );
    }
}

void Particle::resetAcceleration() {
    acceleration = Vec3( 0, 0, 0 );
}

void Particle::makeUnmovable() {
    movable = false;
}

void Particle::offsetPos ( const Vec3 v ) {
    if ( movable ) {
        pos = pos + v;
    }
}

void Particle::addToNormal( Vec3 normal ) {
    accumulated_normal = accumulated_normal + normal.normalized();
}

void Particle::resetNormal() {
    accumulated_normal = Vec3( 0, 0, 0 );
}

Vec3& Particle::getPos() {
    return pos;
}

Vec3 Particle::getNormal() {
    return accumulated_normal;
}
