#include "constraint.h"
#include "particle.h"
#include "vec3.h"

Constraint::Constraint( Particle * _p1, Particle * _p2 ) {
    p1 = _p1;
    p2 = _p2;
    Vec3 vec = p1 -> getPos() - p2 -> getPos();
    rest_distance = vec.length();
}

void Constraint::satisfyConstraint() {
    Vec3 p1_to_p2 = p2 -> getPos() - p1 -> getPos();
    float current_distance = p1_to_p2.length();
    Vec3 correctionVector = 
        p1_to_p2 * ( 1 - rest_distance / current_distance );
    Vec3 correctionVectorHalf = correctionVector * 0.5;
    p1 -> offsetPos ( correctionVectorHalf );
    p2 -> offsetPos ( -correctionVectorHalf ); 
}