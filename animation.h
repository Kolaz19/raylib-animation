#ifndef RAYLIB_ANIMATION
#define RAYLIB_ANIMATION

#include "include/raylib.h"

typedef struct Spritesheet Spritesheet;
typedef struct Animation Animation;

struct Spritesheet {
    Texture2D texture;
    int amountFramesX;
    int amountFramesY;
};

typedef enum AnimationType {
    LOOP,
    PLAY_ONCE
} AnimationType;

typedef enum FlipAxis {
    FLIPX,
    FLIPY,
} FlipAxis;

struct Animation {
    Spritesheet* spriteSheet;
    int startFrame;
    int endFrame;
    int currentFrame;
    float flipShiftX;
    float flipShiftY;
    bool flipX;
    bool flipY;
    FlipAxis flipMode;
    Rectangle origin;
    float frameDuration;
    float advancedTime;
    AnimationType type;
    bool isPlaying;
};


Spritesheet LoadSpritesheet(const char* fileName,  int amountFramesX, int amountFramesY);
void unloadSpritesheet(Spritesheet* spriteSheet);

Animation createAnimation(Spritesheet* spriteSheet, int startFrame, int endFrame, float frameDuration, AnimationType type);
void drawAnimation(Animation* animation, Rectangle* destination, Vector2* origin, float rotation);
void advanceAnimation(Animation* animation);
void startAnimation(Animation* animation);
void stopAnimation(Animation* animation);
void enableAnimation(Animation* animation);
void disableAnimation(Animation* animation);
int getCurrentFrame(Animation* animation);
bool startOfFrame(Animation* animation);
void setShiftValues(Animation* animation, float shiftValueX, float shiftValueY);
void flip(Animation* animation, FlipAxis axis);
void flipReset(Animation* animation, FlipAxis axis);
#endif
