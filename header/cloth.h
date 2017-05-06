#ifndef _CLOTH_
#define _CLOTH_

#include "particle.h"
#include "constraint.h"
#include <vector>

class Cloth {
    private:
        int num_particles_width;
        int num_particles_height;

        std::vector<Particle> particles;
        std::vector<Constraint> constraints;

        void makeConstraint ( Particle *p1, Particle *p2 );
        Vec3 calcTriangleNormal ( Particle *p1, Particle *p2, Particle *p3);
        void addWindForcesForTriangle ( Particle *p1, Particle *p2,
            Particle *p3, const Vec3 direction );
        void update_particle_constraint ( );
        void update_particle_formation ();

    public:
        Cloth ( float width, float height, 
            int num_particles_width, int num_particles_height );
        void build( float width, float height,
            int num_particles_width, int num_particles_height );
        Particle * getParticle ( int x , int y );
        Cloth () {}
        void addForce ( const Vec3 direction );
        void windForce( const Vec3 direction );
        void ball_collision( const Vec3 center, const float radius );
        void update_properties();
        int get_particles_height();
        int get_particles_width();
};

#endif