#ifndef _CONSTRAINT_
#define _CONSTRAINT_

#include "particle.h"

class Constraint {
    private:
        float rest_distance;
    
    public:
        Particle *p1 , *p2;
        Constraint( Particle *p1, Particle *p2);
        void satisfyConstraint();
};

#endif