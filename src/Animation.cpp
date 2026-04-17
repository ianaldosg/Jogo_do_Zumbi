#include "../include/Animation.h"

Animation::Animation() : frameStart(0), frameEnd(0), frameTime(0){}

Animation::Animation(int frameStart, int frameEnd, float frameTime) 
    : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {}
