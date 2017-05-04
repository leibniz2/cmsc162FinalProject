#include "values.h"

#include <stddef.h>

Values* Values::m_pInstance = NULL;

Values* Values::Instance() {
    if( !m_pInstance ) {
        m_pInstance = new Values;
    }
    return m_pInstance;
}

Values::Values() {
    constraint_factor = 1;
    gravity_factor = 1;
    wind_factor = 1;
    ball_style_no = 0 ;
    cloth_style_no = 0;
    // ball_status = 0;
    // cloth_status = 1;
}

float Values::get_cfactor() {
    return constraint_factor;
}

float Values::get_gfactor() {
    return gravity_factor;
}

float Values::get_wfactor() {
    return wind_factor;
}

float Values::get_bstyle_no() {
    return ball_style_no;
}

float Values::get_cstyle_no() {
    return cloth_style_no;
}

// int Values::has_ball() {
//     return ball_status;
// }

// int Values::has_cloth() {
//     return cloth_status;
// }

void Values::set_cfactor( float s ) {
    constraint_factor = s;
}

void Values::set_gfactor( float s ) {
    gravity_factor = s;
}

void Values::set_wfactor( float s ) {
    wind_factor = s;
}

void Values::set_bstyle_no( float s ) {
    ball_style_no = s;
}

void Values::set_cstyle_no( float s ) {
    cloth_style_no = s;
}

// void Values::set_ball( bool s ) {
//     ball_status = s;
// }

// void Values::set_cloth( bool s ) {
//     cloth_status = s;
// }
