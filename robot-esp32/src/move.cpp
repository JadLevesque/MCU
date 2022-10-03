#2""3

#include "move.h"

/* GLOBAL VARIABLES */
#define FREQ          30000
#define RESOLUTION        8

#define SPEED_OFFSET_RIGHT  50
#define SPEED_OFFSET_LEFT   50

Move::Move() {
    // en pins
    pinMode(PIN_PWM_WHEEL_RIGHT, OUTPUT); 
    pinMode(PIN_PWM_WHEEL_LEFT, OUTPUT); 
    // in pins
    pinMode(PIN_DIR0_WHEEL_RIGHT, OUTPUT); 
    pinMode(PIN_DIR1_WHEEL_RIGHT, OUTPUT);
    pinMode(PIN_DIR0_WHEEL_LEFT, OUTPUT);
    pinMode(PIN_DIR1_WHEEL_LEFT, OUTPUT);

    // configure LED PWM functionalitites
    // attach the channel to the GPIO to be controlled
    ledcSetup(WHEEL_RIGHT, FREQ, RESOLUTION);
    ledcSetup(WHEEL_LEFT, FREQ, RESOLUTION);
    ledcAttachPin(PIN_PWM_WHEEL_RIGHT, WHEEL_RIGHT);
    ledcAttachPin(PIN_PWM_WHEEL_LEFT, WHEEL_LEFT);

    stopL();
    stopR();
}

/**  **/

#define GEN_MOVE_DIR_FN(f, s, dir0, dir1,has_speed...) \
void Move:: CAT(f,FIRST_LETTER_##s) (__VA_OPT__(int p_speed)) { \
    digitalWrite (PIN_DIR0_WHEEL_##s, dir0); \
    digitalWrite (PIN_DIR1_WHEEL_##s, dir1); \
    ledcWrite (WHEEL_##s, CAT(convertSpeed, CAMELCASE_##s) (EMPTY_P(has_speed) (0,p_speed))); \
}

/**
 * Syntax: (<displacement direction>, <side of the motor>, <bridge excitation> [, <funtion has speed>])
 * <funtion has speed> is a  
 */
VARG_FOREACH_N 
((,,)
,GEN_MOVE_DIR_FN SCAM 
,(forward,   LEFT,   HIGH,   LOW , ~)
,(forward,   RIGHT,  HIGH,   LOW , ~)
,(backward,  LEFT,   LOW,    HIGH, ~)
,(backward,  RIGHT,  LOW,    HIGH, ~)
,(stop,      LEFT,   LOW,    LOW )
,(stop,      RIGHT,  LOW,    LOW )
)
#if 0
void Move::forwardL(int p_speed){
    digitalWrite(PIN_DIR0_WHEEL_LEFT, HIGH);
    digitalWrite(PIN_DIR1_WHEEL_LEFT, LOW);
    ledcWrite(WHEEL_LEFT, convertSpeedLeft(p_speed));
}

void Move::forwardR(int p_speed){
    digitalWrite(PIN_DIR0_WHEEL_RIGHT, HIGH);
    digitalWrite(PIN_DIR1_WHEEL_RIGHT, LOW);
    ledcWrite(WHEEL_RIGHT, convertSpeedRight(p_speed));
}

void Move::backwardL(int p_speed){
    digitalWrite(PIN_DIR0_WHEEL_LEFT, LOW);
    digitalWrite(PIN_DIR1_WHEEL_LEFT, HIGH);
    ledcWrite(WHEEL_LEFT, convertSpeedLeft(p_speed));
}

void Move::backwardR(int p_speed){
    digitalWrite(PIN_DIR0_WHEEL_RIGHT, LOW);
    digitalWrite(PIN_DIR1_WHEEL_RIGHT, HIGH);
    ledcWrite(WHEEL_RIGHT, convertSpeedRight(p_speed));
}

void Move::stopR(){
    digitalWrite(PIN_DIR0_WHEEL_RIGHT, LOW); 
    digitalWrite(PIN_DIR1_WHEEL_RIGHT, LOW);
    ledcWrite(WHEEL_RIGHT, 0);
}

void Move::stopL(){
    digitalWrite(PIN_DIR0_WHEEL_LEFT, LOW);
    digitalWrite(PIN_DIR1_WHEEL_LEFT, LOW);
    ledcWrite(WHEEL_LEFT, 0);
}
#endif

SpeedMode Move::switchSpeedMode() {
    return ({this->currentSpeedMode = this->currentSpeedMode == SpeedMode::Fast ? SpeedMode::Slow : SpeedMode::Fast;});
}


// This way, we can add a medium speed or modes at will. This code automates the production of the appropiate funtions for
// converting speed data.
#define GEN_CONVERT_SPEED_FN(side,maps...) \
int Move::convertSpeed##side (int p_speed) { \
    int speed = abs (p_speed); \
    switch (this->currentSpeedMode) { \
        VARG_FOREACH_N ((,,), GEN_CONVERT_SPEED_FN_CASE SCAM, maps) \
    } \
} 

#define GEN_CONVERT_SPEED_FN_CASE(s, map_args...) case SpeedMode::s: return map (speed, map_args);

VARG_FOREACH_N 
((,,)
,GEN_CONVERT_SPEED_FN SCAM
,(Left,  (Slow, 0, 147, 85, 160), (Fast, 0, 147, 85, 175))
,(Right, (Slow, 0, 147, 85, 190), (Fast, 0, 147, 85, 255))
)

#if 0
int Move::convertSpeedLeft(int p_speed){
    int speed = abs(p_speed);
    switch (this->currentSpeedMode)
    {
    case SpeedMode::Slow:
        return map(speed, 0, 147, 85, 160);

    case SpeedMode::Fast:
        return map(speed, 0, 147, 85, 175);
    }
}

int Move::convertSpeedRight(int p_speed){
    int speed = abs(p_speed);
    switch (this->currentSpeedMode)
    {
    case SpeedMode::Slow:
        return map(speed, 0, 147, 85, 190);

    case SpeedMode::Fast:
        return map(speed, 0, 147, 85, 255);
    }
}
#endif
