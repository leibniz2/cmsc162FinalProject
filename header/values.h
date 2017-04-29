#ifndef _VALUES_
#define _VALUES_

#define DAMPING 0.01
#define STEP_SIZE 0.25
#define CONSTRAINT_ITERATIONS 15

class Values {
    private:
        int step_size;
    
    public:
        Values() {}
        void set_step_size(float x);
        float get_step_size();
        
};

#endif