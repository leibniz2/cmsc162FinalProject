#ifndef _VALUES_
#define _VALUES_

#define DAMPING 0.01
#define STEP_SIZE 0.5*0.5
#define CONSTRAINT_ITERATIONS 15

#define WIND_MULT 0.3
#define GRAVITY_MULT -0.2

class Values {
    private:

        float constraint_factor; // const * factor
        float wind_factor;
        float gravity_factor;

        int ball_style_no;
        int cloth_style_no; 
        // int ball_status; // is shown or hidden
        // int cloth_status; // is shown or hidden


        // view related flags
        // bool stateChanged; // tracks whether there is a change in value   
        Values();
        static Values* m_pInstance;       
    
    public:

        float get_cfactor();
        float get_gfactor();
        float get_wfactor();
        
        float get_bstyle_no();
        float get_cstyle_no();

        // int has_ball();
        // int has_cloth();

        void set_cfactor( float s );
        void set_gfactor( float s );
        void set_wfactor( float s );
        
        void set_bstyle_no( float s );
        void set_cstyle_no( float s );
        
        // void set_ball( bool s );
        // void set_cloth( bool s );

        static Values* Instance();
};

#endif