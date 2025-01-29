#pragma once

#include "vex.h"
#include "pid.h"
#include "devices.h"

#define lb LadyBrown::getInstance()

class LadyBrown {
    private:
        int target = 0;
        int pos_deadzone = 1;
        int vel_deadzone = 0.1;
        int ff_K = 0;
        bool on = true;
        bool at_target = true;
        vex::task update_task;
        PID lb_pid = PID(0.2, 0.0, 0.0);
        LadyBrown() = default;
	    LadyBrown(const LadyBrown&) = delete;
	    LadyBrown& operator=(const LadyBrown&) = delete;
    public:
        inline static LadyBrown& getInstance() {
    		static LadyBrown INSTANCE;
	    	return INSTANCE;
	    }   
        void func();
        void update();
        void initialize();
        void off();
        bool done();
        void move(int cur_target, bool blocking=false);
};