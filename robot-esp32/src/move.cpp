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

