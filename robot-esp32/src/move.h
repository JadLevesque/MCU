#ifndef __MOVE_H__
#define __MOVE_H__

#include <Arduino.h>
#include "pins.h"

enum SpeedMode {Slow, Fast};

class Move{
    public:
        Move();

        void forwardL(int p_speed);
        void forwardR(int p_speed);

        void backwardL(int p_speed);
        void backwardR(int p_speed);

        void stopR();
        void stopL();

        SpeedMode switchSpeedMode();

    private:
        SpeedMode currentSpeedMode = SpeedMode::Slow;
        int convertSpeedLeft(int p_speed);
        int convertSpeedRight(int p_speed);
};
#endif // __MOVE_H__