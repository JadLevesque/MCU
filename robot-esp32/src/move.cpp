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

SpeedMode Move::switchSpeedMode() {
    if (currentSpeedMode == SpeedMode::Slow) {
        currentSpeedMode = SpeedMode::Fast;
    }
    else if (currentSpeedMode == SpeedMode::Fast) {
        this->currentSpeedMode = SpeedMode::Slow;
    }
    return currentSpeedMode;
}


#define PRAGMA(p...) _Pragma(#p)
#define PRINT_ERROR_I(m...) PRAGMA(GCC error #m)
#define PRINT_ERROR(m...) PRINT_ERROR_I(m)
#define FX(f,x) f x
#define MACRO_PUSH(m) DUMP(PRAGMA(push_macro(#m)))
#define MACRO_POP(m) DUMP(PRAGMA(pop_macro(#m)))
#define EAT(...)
#define DUMP(v...) EAT(v)
#define REVIVE(m) MACRO_PUSH(m)MACRO_POP(m)
#define SCAN(v...) REVIVE(SCAN) v
#define NIF_0(t,f...) REVIVE(NIF_0) t
#define NIF_1(t,f...) REVIVE(NIF_0) f
#define EMPTY_P(...) NIF_##__VA_OPT__(1)

#define VARG_DEC(x,xs...) REVIVE(ARG_DEC) (xs##__VA_OPT__())

#define VARG_MAP(f,xs...) REVIVE(VARG_MAP) __VA_OPT__(VARG_MAP_I(f,xs))
#define VARG_MAP_I(f,x,xs...) REVIVE(VARG_MAP_I) f(x)__VA_OPT__(,VARG_MAP_I(f,xs))

#define VARG_FOREACH(f,xs...) REVIVE(VARG_FOREACH) __VA_OPT__(VARG_FOREACH_I(f,xs))
#define VARG_FOREACH_I(f,x,xs...) REVIVE(VARG_FOREACH_I) f(x) __VA_OPT__()

#define APP_BRACKET(x) {x}

PRINT_ERROR
(VARG_MAP (APP_BRACKET, 1,2,3,4)
)

int Move::convertSpeedLeft(int p_speed){
    int speed = abs(p_speed);
    switch (this->currentSpeedMode)
    {
    case SpeedMode::Slow:
        return map(speed, 0, 147, 85, 160);

    case SpeedMode::Fast:
        return map(speed, 0, 147, 85, 175);
    
    default:
        return 0;
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
    
    default:
        return 0;
    }
}

