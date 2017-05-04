#include "cloth.h"
#include "particle.h"
#include "constraint.h"
#include "values.h"
#include <vector>
#include <cstdio>

static Values* v = Values::Instance();

Particle * Cloth::getParticle( int x, int y ) {
    return &particles [ y * num_particles_width + x ];
}

void Cloth::makeConstraint( Particle * p1, Particle * p2 ) {
    constraints.push_back( Constraint ( p1, p2) );
}

void Cloth::build( float width, float height,
    int _num_particles_width, int _num_particles_height ) {
         num_particles_height = _num_particles_height;
        num_particles_width = _num_particles_width;
        particles.resize( num_particles_width * num_particles_height );

        for(int x=0; x<num_particles_width; x++){
                for(int y=0; y<num_particles_height; y++){
                    Vec3 pos = Vec3(width * (x/(float)num_particles_width),
                                    -height * (y/(float)num_particles_height),
                                    0);
                    particles[y*num_particles_width+x]= Particle(pos); // insert particle in column x at y'th row
                }
            }

        // Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
        for(int x=0; x<num_particles_width; x++){
            for(int y=0; y<num_particles_height; y++){
                if (x<num_particles_width-1) makeConstraint(getParticle(x,y),getParticle(x+1,y));
                if (y<num_particles_height-1) makeConstraint(getParticle(x,y),getParticle(x,y+1));
                if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(getParticle(x,y),getParticle(x+1,y+1));
                if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(getParticle(x+1,y),getParticle(x,y+1));
            }
        }


        // Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
        for(int x=0; x<num_particles_width; x++) {
            for(int y=0; y<num_particles_height; y++)
            {
                if (x<num_particles_width-2) makeConstraint(getParticle(x,y),getParticle(x+2,y));
                if (y<num_particles_height-2) makeConstraint(getParticle(x,y),getParticle(x,y+2));
                if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(getParticle(x,y),getParticle(x+2,y+2));
                if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(getParticle(x+2,y),getParticle(x,y+2));			}
        }


        // making the upper left most three and right most three particles unmovable
        for(int i=0;i<3; i++){
            getParticle(0+i ,0)->offsetPos(Vec3(0.5,0.0,0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
            getParticle(0+i ,0)->makeUnmovable(); 

            getParticle(0+i ,0)->offsetPos(Vec3(-0.5,0.0,0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
            getParticle(num_particles_width-1-i ,0)->makeUnmovable();
        }        
 }

Vec3 Cloth::calcTriangleNormal ( Particle *p1, Particle *p2, Particle *p3 ) {
    Vec3 pos1 = p1 -> getPos();
    Vec3 pos2 = p2 -> getPos();
    Vec3 pos3 = p3 -> getPos();

    Vec3 v1 = pos2 - pos1;
    Vec3 v2 = pos3 - pos1;

    return v1.cross ( v2 );
}

void Cloth::addWindForcesForTriangle(Particle * p1, Particle *p2, 
    Particle * p3, const Vec3 direction ) {
        Vec3 normal = calcTriangleNormal ( p1, p2, p3 );
        Vec3 d = normal.normalized();
        Vec3 force = normal * ( d.dot(direction) );
        p1 -> addForce ( force );
        p2 -> addForce ( force );
        p3 -> addForce ( force );
}

Cloth::Cloth( float width, float height, 
    int _num_particles_width, int _num_particles_height ) {
        num_particles_height = _num_particles_height;
        num_particles_width = _num_particles_width;
        particles.resize( num_particles_width * num_particles_height );

        for(int x=0; x<num_particles_width; x++){
                for(int y=0; y<num_particles_height; y++){
                    Vec3 pos = Vec3(width * (x/(float)num_particles_width),
                                    -height * (y/(float)num_particles_height),
                                    0);
                    particles[y*num_particles_width+x]= Particle(pos); // insert particle in column x at y'th row
                }
            }

        // Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
        for(int x=0; x<num_particles_width; x++){
            for(int y=0; y<num_particles_height; y++){
                if (x<num_particles_width-1) makeConstraint(getParticle(x,y),getParticle(x+1,y));
                if (y<num_particles_height-1) makeConstraint(getParticle(x,y),getParticle(x,y+1));
                if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(getParticle(x,y),getParticle(x+1,y+1));
                if (x<num_particles_width-1 && y<num_particles_height-1) makeConstraint(getParticle(x+1,y),getParticle(x,y+1));
            }
        }


        // Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
        for(int x=0; x<num_particles_width; x++) {
            for(int y=0; y<num_particles_height; y++)
            {
                if (x<num_particles_width-2) makeConstraint(getParticle(x,y),getParticle(x+2,y));
                if (y<num_particles_height-2) makeConstraint(getParticle(x,y),getParticle(x,y+2));
                if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(getParticle(x,y),getParticle(x+2,y+2));
                if (x<num_particles_width-2 && y<num_particles_height-2) makeConstraint(getParticle(x+2,y),getParticle(x,y+2));			}
        }


        // making the upper left most three and right most three particles unmovable
        for(int i=0;i<3; i++){
            getParticle(0+i ,0)->offsetPos(Vec3(0.5,0.0,0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
            getParticle(0+i ,0)->makeUnmovable(); 

            getParticle(0+i ,0)->offsetPos(Vec3(-0.5,0.0,0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
            getParticle(num_particles_width-1-i ,0)->makeUnmovable();
        }
}

void Cloth::update_particle_formation() {
    std::vector<Particle>::iterator particle;
     // reset normals (which where written to last frame)
    for(particle = particles.begin(); particle != particles.end(); particle++) {
        (*particle).resetNormal();
    }

    //create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
    for(int x = 0; x<num_particles_width-1; x++) {
        for(int y=0; y<num_particles_height-1; y++)
        {
            Vec3 normal = calcTriangleNormal(getParticle(x+1,y),getParticle(x,y),getParticle(x,y+1));
            getParticle(x+1,y)->addToNormal(normal);
            getParticle(x,y)->addToNormal(normal);
            getParticle(x,y+1)->addToNormal(normal);

            normal = calcTriangleNormal(getParticle(x+1,y+1),getParticle(x+1,y),getParticle(x,y+1));
            getParticle(x+1,y+1)->addToNormal(normal);
            getParticle(x+1,y)->addToNormal(normal);
            getParticle(x,y+1)->addToNormal(normal);
        }
    }
}

void Cloth::update_particle_constraint () {
    std::vector<Constraint>::iterator constraint;
    for(int i=0; i<CONSTRAINT_ITERATIONS * (v -> get_cfactor()); i++) {
        for(constraint = constraints.begin(); constraint != constraints.end(); constraint++ ) {
            (*constraint).satisfyConstraint(); // satisfy constraint.
        }
    }

    std::vector<Particle>::iterator particle;
    for(particle = particles.begin(); particle != particles.end(); particle++) {
        (*particle).timeStep(); // calculate the position of each particle at the next time step.
    }
}

void Cloth::addForce(const Vec3 direction) {
    std::vector<Particle>::iterator particle;
    for(particle = particles.begin(); particle != particles.end(); particle++) {
        (*particle).addForce(direction); // add the forces to each particle
    }

}

void Cloth::update_properties() {
    float wx = v -> get_wfactor() * WIND_MULT;
    float wy = v -> get_gfactor() * GRAVITY_MULT ;
    addForce( Vec3(0, wy, 0 ) * STEP_SIZE ); // add gravity pointing down
    windForce( Vec3(wx, 0, 0.2 * wx) * STEP_SIZE ); // generatae some wind
    update_particle_constraint();
    update_particle_formation();
}

	/* used to add wind forces to all particles, is added for each triangle since the final force is proportional to the triangle area as seen from the wind direction*/
void Cloth::windForce(const Vec3 direction) {
    for(int x = 0; x<num_particles_width-1; x++) {
        for(int y=0; y<num_particles_height-1; y++) {
            addWindForcesForTriangle(getParticle(x+1,y),getParticle(x,y),getParticle(x,y+1),direction);
            addWindForcesForTriangle(getParticle(x+1,y+1),getParticle(x+1,y),getParticle(x,y+1),direction);
        }
    }
}

int Cloth::get_particles_height() {
    return num_particles_height;
}

int Cloth::get_particles_width() {
    return num_particles_width;
}