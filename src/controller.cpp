#include <cstdio>

#include "controller.h"
#include "values.h"

Controller::Controller() {}
void Controller::callback_fn( int control_id ) {
    switch ( control_id ) {
        case DAMPING_LISTBOX:
            printf ("DAMPING LIST BOX ITEM CHANGED");
        break;
        case VELOCITY_LISTBOX:
            printf ("VELOCITY LIST BOX ITEM CHANGED");
        break;
        case CLOTH_LISTBOX:
            printf ("CLOTH LIST BOX ITEM CHANGED");
        break;
        case BALL_LISTBOX:
            printf ("BALL LIST BOX ITEM CHANGED");
        break;
        case APPLY_BUTTON:
            printf ("APPLY BUTTON ITEM CHANGED");
        break;
        case DEFAULT_BUTTON:
            printf ("DEFAULT BUTTON ITEM CHANGED");
        break;
        default:
            printf ("Uncaught exception from GLUI callback");
    }
}