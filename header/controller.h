#ifndef _CONTROLLER_
#define _CONTROLLER_


class Controller {
    private:
        int rigidity_item_id; // done
        int gravity_item_id; // done
        int wind_item_id; // done
        int cloth_item_id; // done
        int ball_item_id; 
        int has_cloth_id;
        int has_ball_id;
        float translate_xy[2] = { -10.0f, 6.0f };
        float rotation_matrix[16] = 
        { 1.0, 0.0, 0.0, 0.0, 
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0, 
          0.0, 0.0, 0.0, 1.0  };	
        Controller();
        static Controller* c_pInstance;

    public:
        enum Type {
            RIGIDITY_LISTBOX = 0,
            GRAVITY_LISTBOX,
            WIND_LISTBOX,
            CLOTH_LISTBOX,
            BALL_LISTBOX,
            TRANSLATION_XY
        };

        enum Slider {
            NEG_75 = 1,
            NEG_50,
            NEG_25,
            S_DEFAULT, // 1.0x
            POS_25,
            POS_50,
            POS_2X,
            NONE
        };

        enum CLOTH_STYLE {
            CS_DEFAULT = 0, // SOLID_WHITE
            SOLID_GREEN,
            CHECKER_BW,
            FLAG_PH
        };

        enum BALL_STYLE {
            BS_DEFAULT = 0, // SOLID_BLACK
            SOLID_RED,
            SOLID_GRAY
        };

        int g_has_cloth_id_val();
        int g_has_ball_id_val();
        int g_cloth_item_id_val();
        int g_ball_item_id_val();

        int * g_has_gravity_id();
        int * g_wind_item_id();
        int * g_rigidity_item_id();
        int * g_gravity_item_id();
        int * g_cloth_item_id();
        int * g_ball_item_id();
        int * g_has_cloth_id();
        int * g_has_ball_id();
        float * g_translatexy_id();
        float * g_rotation_id();

        void callback_fn ( int control_id );
        void keyboard( unsigned char key, int x, int y );
        void special( int key, int x, int y );
        float setSlider( int value_id );
        static Controller* Instance();
};

#endif
