#include "main.h";
using namespace okapi;

namespace tilter {
    tilterState curState;

    pros::ADIDigitalOut tilt(TILT);
    pros::ADIDigitalOut bclamp(BCLAMP);

    void init() {
        bclamp.set_value(1);
        tilt.set_value(0);
        curState = soft;
    }

    void act() {
        switch(curState) {
            case hard:
                tilt.set_value(1);
                pros::delay(50);
                bclamp.set_value(0);
                break;
            case soft:
                bclamp.set_value(1);
                pros::delay(50);
                tilt.set_value(0);
                break;
        }
    }

    void update() {
        if (controller.getDigital(ControllerDigital::B)) {
            curState = hard;
        } else if (controller.getDigital(ControllerDigital::X)) {
            curState = soft;
        }
    }
}