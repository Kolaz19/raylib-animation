#ifndef RAYLIB_ANIMATION
#define RAYLIB_ANIMATION

#include "include/raylib.h"

typedef struct Spritesheet Spritesheet;
Spritesheet LoadSpritesheet(const char* fileName, int amountFrames, int frameWidth, int frameHeight);
void unloadSpritesheet(Spritesheet spriteSheet);


#endif
