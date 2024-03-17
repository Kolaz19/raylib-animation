#ifndef RAYLIB_ANIMATION
#define RAYLIB_ANIMATION

#include "include/raylib.h"

typedef struct Spritesheet Spritesheet;
typedef struct Animation Animation;

struct Spritesheet {
    Texture2D texture;
    int frameWidth;
    int frameHeight;
};

typedef enum AnimationType {
    LOOP,
    PLAY_ONCE
} AnimationType;

struct Animation {
    Spritesheet* spriteSheet;
    int startFrame;
    int endFrame;
    int currentFrame;
    float frameDuration;
    float advancedTime;
    AnimationType type;
    bool isPlaying;
};

Spritesheet LoadSpritesheet(const char* fileName,  int frameWidth, int frameHeight);
void unloadSpritesheet(Spritesheet* spriteSheet);

Animation createAnimation(Spritesheet* spriteSheet, int startFrame, int endFrame, float frameDuration, AnimationType type);
void drawAnimation(Animation* animation, float posX, float posY, float width, float height, float originX,float originY, float rotation );
void advanceAnimation(Animation* animation);
#endif
