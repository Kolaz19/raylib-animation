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
// From left to right, row to row, set start and end frame of the animation
// Set frame duration in seconds
// AnimationType LOOP resets to first frame after last frame was finished in advanceAnimation
// AnimationType PLAY_ONCE disables animation after last frame was finished in advanceAnimation
Animation createAnimation(Spritesheet* spriteSheet, int startFrame, int endFrame, float frameDuration, AnimationType type);
void drawAnimation(Animation* animation, Rectangle* destination, Vector2* origin, float rotation);

// Set a new origin rectangle after a specific amount of time.
void advanceAnimation(Animation* animation);
// Reset advanced time, reset to startFrame and enable animation
void startAnimation(Animation* animation);
// Reset advanced time, reset to startFrame and disable animation
void stopAnimation(Animation* animation);
// Enable function of advanceAnimation and drawAnimation
void enableAnimation(Animation* animation);
// Disable function of advanceAnimation and drawAnimation
void disableAnimation(Animation* animation);
int getCurrentFrame(Animation* animation);
// Return true if animation was switched to start of frame by advanceAnimation
bool startOfFrame(Animation* animation);
// Mandatory for flipped frames when texture is not centered on frame
void setShiftValues(Animation* animation, float shiftValueX, float shiftValueY);
// Toggle flipped drawing in drawAnimation
void flip(Animation* animation, FlipAxis axis);
// Toggle un-flipped drawing in drawAnimation
void flipReset(Animation* animation, FlipAxis axis);
#endif
