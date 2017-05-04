#include <cstdio>
#include <stddef.h>

#include "controller.h"
#include "values.h"

static Values* v = Values::Instance();

Controller* Controller::c_pInstance = NULL;

Controller* Controller::Instance() {
    if( !c_pInstance ) {
        c_pInstance = new Controller;
    }
    return c_pInstance;
} 

Controller::Controller() {
    rigidity_item_id = 4;
    gravity_item_id = 4;
    wind_item_id = 4;
    cloth_item_id = 0;
    ball_item_id = 0;
    has_cloth_id = 1;
    has_ball_id = 0;
}

float Controller::setSlider( int value_id ) {
    float v;
    if ( value_id == NEG_75 ) {
        printf("0.75");
        v = 0.75;
    } else if ( value_id == NEG_50 ) {
         printf("0.50");
        v = 0.50;
    } else if ( value_id == NEG_25 ) {
         printf("0.25");
        v = 0.25;
    } else if ( value_id == POS_25 ) {
         printf("1.25");
        v = 1.25;
    } else if ( value_id == POS_50 ) {
         printf("1.50");
        v = 1.50;
    } else if ( value_id == POS_2X ) {
         printf("2.00");
        v = 2.0;
    } else if ( value_id == NONE ) {
        v = 0.0;
    } else {
        v = 1.0;
    }
    
    return v;
}

void Controller::callback_fn( int control_id ) {
    switch ( control_id ) {
        case RIGIDITY_LISTBOX:
            v -> set_cfactor( setSlider(rigidity_item_id) );
        break;
        case GRAVITY_LISTBOX:
            if ( gravity_item_id < 4 ) {
                v -> set_gfactor( setSlider(gravity_item_id) * -1.0 );
            } else {
                 v -> set_gfactor( setSlider(gravity_item_id) );
            }       
        break;
        case WIND_LISTBOX:
            v -> set_wfactor( setSlider(wind_item_id) );
        break;
        case CLOTH_LISTBOX:
            printf ("CLOTH LIST BOX ITEM CHANGED");
        break;
        case BALL_LISTBOX:
            printf ("BALL LIST BOX ITEM CHANGED");
        break;
        case TRANSLATION_XY:
            printf ("%f, %f \n", translate_xy[0], translate_xy[1]);
        break;
        default:
            printf ("Uncaught exception from GLUI callback");
    }
}


// void Controller::s_wind_item_id(int s ){
//     wind_item_id = s;
// }

// void Controller::s_rigidity_item_id(int s ){
//     rigidity_item_id = s;
// }

// void Controller::s_gravity_item_id(int s ){
//     gravity_item_id = s;
// }

int* Controller::g_wind_item_id(){
    return &wind_item_id;
}

int* Controller::g_rigidity_item_id(){
    return &rigidity_item_id;
}

int* Controller::g_gravity_item_id(){
    return &gravity_item_id;
}


// void Controller::s_cloth_item_id(int s ){
//     cloth_item_id = s;
// }

// void Controller::s_ball_item_id(int s ){
//     ball_item_id = s;
// }

int Controller::g_has_cloth_id_val() {
    return has_cloth_id;
}

int Controller::g_has_ball_id_val() {
    return has_ball_id;
}

int* Controller::g_cloth_item_id(){
    return &cloth_item_id;
}

int* Controller::g_ball_item_id(){ 
    return &ball_item_id;
}

int* Controller::g_has_cloth_id() {
    return &has_cloth_id;
}

int* Controller::g_has_ball_id() {
    return &has_ball_id;
}

float* Controller::g_translatexy_id() {
    return &translate_xy[0];
}

// float[] Controller::g_translatexy_id_val() {
//     return translate_xy;
// }