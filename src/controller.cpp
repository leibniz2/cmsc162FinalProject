
#include <GL/glut.h>

#include "controller.h"
#include "values.h"

#define XY_SPEED 0.05

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
        v = 0.75;
    } else if ( value_id == NEG_50 ) {
        v = 0.50;
    } else if ( value_id == NEG_25 ) {
        v = 0.25;
    } else if ( value_id == POS_25 ) {
        v = 1.25;
    } else if ( value_id == POS_50 ) {
        v = 1.50;
    } else if ( value_id == POS_2X ) {
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
            
        break;
        case BALL_LISTBOX:
            
        break;
        case TRANSLATION_XY:
            
        break;
        default: {}
    }
}

void Controller::keyboard( unsigned char key, int x, int y ) {
    switch( key ) {
        case 'r':
            translate_xy[0] = -10.00f;
            translate_xy[1] = 6.0f;
        break;
        case 'R':
           translate_xy[0] = -10.00f;
            translate_xy[1] = 6.0f;
        break;
        default:{}
    }
}

void Controller::special( int key, int x, int y ){
    switch( key ) {
        case GLUT_KEY_UP:
            translate_xy[1] += XY_SPEED;
        break;
        case GLUT_KEY_DOWN:
            translate_xy[1] -= XY_SPEED;
        break;
        case GLUT_KEY_LEFT:
            translate_xy[0] -= XY_SPEED;
        break;
        case GLUT_KEY_RIGHT:
            translate_xy[0] += XY_SPEED;
        break;
        default:{}
    }
}

int* Controller::g_wind_item_id(){
    return &wind_item_id;
}

int* Controller::g_rigidity_item_id(){
    return &rigidity_item_id;
}

int* Controller::g_gravity_item_id(){
    return &gravity_item_id;
}

int Controller::g_has_cloth_id_val() {
    return has_cloth_id;
}

int Controller::g_has_ball_id_val() {
    return has_ball_id;
}

int Controller::g_cloth_item_id_val() {
    return cloth_item_id;
}

int Controller::g_ball_item_id_val() {
    return ball_item_id;
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

float* Controller::g_rotation_id() {
    return &rotation_matrix[0];
}
