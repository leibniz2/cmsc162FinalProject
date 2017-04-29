#ifndef _CONTROLLER_
#define _CONTROLLER_

class Controller {
    private:
        

    public:
        enum Type {
            DAMPING_LISTBOX = 0,
            VELOCITY_LISTBOX,
            CLOTH_LISTBOX,
            BALL_LISTBOX,
            APPLY_BUTTON,
            DEFAULT_BUTTON
        };
        Controller();
        void callback_fn ( int control_id );
};

#endif