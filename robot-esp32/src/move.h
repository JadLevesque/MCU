#ifndef __MOVE_H__
#define __MOVE_H__

#include <Arduino.h>
#include "ppmp.h"
#include "pins.h"

enum SpeedMode {Slow, Fast};

class Interpolation {
    public:
        int interpolate (int x);
        void setFromLow (int), setFromHigh (int), setToLow (int), setToHigh (int);
    private:
        int fromLow, fromHigh, toLow, toHigh;
}

class Motor {
    public:
        void forward (int speed), backward (int speed), stop ();
        void setBridge (unsigned A, unsigned B);
        struct {
            struct { struct { void set (unsigned x); } low, high; } from, to;
        } calSpeed; // calibration

    private:
        struct { unsigned a, b; } bridge;
};


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