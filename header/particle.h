#ifndef _PARTICLE_
#define _PARTICLE_

#include "vec3.h"

class Particle {
    private:
        bool movable;
        float mass;
        Vec3 pos;
        Vec3 old_pos;
        Vec3 acceleration;
        Vec3 accumulated_normal;
    
    public:
        Particle( Vec3 pos );
        Particle(){}
        
        void addForce ( Vec3 f );
        void timeStep ();
        void resetAcceleration();
        void makeUnmovable();
        void offsetPos ( const Vec3 v );
        void addToNormal ( Vec3 normal );
        void resetNormal();

        Vec3& getPos();
        Vec3 getNormal();
};

#endif