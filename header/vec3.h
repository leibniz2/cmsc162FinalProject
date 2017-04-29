#ifndef _VEC3_
#define _VEC3_

class Vec3 {
    public:
        float f[3];
        float length ();
        float dot ( const Vec3 &v ); 
        
        Vec3 ( float x, float y, float z );
        Vec3 () {}
        ~Vec3 () {}

        Vec3 normalized ();
        Vec3 operator/ ( const float &a );
        Vec3 operator- ( const Vec3 &v );
        Vec3 operator+ ( const Vec3 &v );
        Vec3 operator* ( const float &a );
        Vec3 operator- ();
        Vec3 cross ( const Vec3 &v );
        
        void operator+= ( const Vec3 &v );
};

#endif