#include "animation.h"
#include "include/raylib.h"

static void setOriginPos(Rectangle* origin, int *currentFrame, int* textureWidth);

Spritesheet LoadSpritesheet(const char* fileName, int amountFramesX, int amountFramesY) {
    Spritesheet spriteSheet;

    Texture2D texture = LoadTexture(fileName);
    spriteSheet.texture = texture;

    spriteSheet.amountFramesX = amountFramesX;
    spriteSheet.amountFramesY = amountFramesY;

    return spriteSheet;
}

void unloadSpritesheet(Spritesheet* spriteSheet) {
    UnloadTexture((spriteSheet->texture));
}

Animation createAnimation(Spritesheet* spriteSheet, int startFrame, int endFrame, float frameDuration, AnimationType type) {
    Animation animation;
    animation.spriteSheet = spriteSheet;
    animation.startFrame = startFrame;
    animation.endFrame = endFrame;
    animation.currentFrame = startFrame;
    animation.frameDuration = frameDuration;
    animation.advancedTime = 0;
    animation.type = type;
    animation.isPlaying = type == LOOP ? true : false; 
    animation.origin.width =  (int)(spriteSheet->texture.width / spriteSheet->amountFramesX);
    animation.origin.height =  (int)(spriteSheet->texture.height / spriteSheet->amountFramesY);
    setOriginPos(&animation.origin, &animation.currentFrame, &animation.spriteSheet->texture.width);

    return animation;
}

void startAnimation(Animation* animation) {
    animation->isPlaying = true;
    animation->currentFrame = animation->startFrame;
    animation->advancedTime = 0;
    setOriginPos(&animation->origin, &animation->currentFrame, &animation->spriteSheet->texture.width);
}

void stopAnimation(Animation* animation) {
    animation->isPlaying = false;
    animation->currentFrame = animation->startFrame;
    animation->advancedTime = 0;
    setOriginPos(&animation->origin, &animation->currentFrame, &animation->spriteSheet->texture.width);
}

void enableAnimation(Animation* animation) {
    animation->isPlaying = true;
}

void disableAnimation(Animation* animation) {
    animation->isPlaying = false;
}

int getCurrentFrame(Animation* animation) {
    return animation->currentFrame - animation->startFrame + 1;
}

bool startOfFrame(Animation* animation) {
    return animation->advancedTime == 0;
}

void advanceAnimation(Animation* animation) {
    if (!animation->isPlaying) {
	return;
    }

    animation->advancedTime += GetFrameTime();
    if (animation->advancedTime >= animation->frameDuration) {
	animation->advancedTime = 0;
	animation->currentFrame++;
    }

    //Loop back to start frame
    if (animation->currentFrame > animation->endFrame) {
	animation->currentFrame = animation->startFrame;
	if (animation->type == PLAY_ONCE) {
	    animation->isPlaying = false;
	}
    }
    //Set new origin when current frame has changed
    if (animation->advancedTime == 0) {
	setOriginPos(&animation->origin, &animation->currentFrame, &animation->spriteSheet->texture.width);
    }
}

void drawAnimation(Animation* animation, Rectangle* destination, Vector2* origin, float rotation ) {
    if (!animation->isPlaying) {
	return;
    }

    DrawTexturePro(animation->spriteSheet->texture, animation->origin, *destination, *origin, rotation,  WHITE);
}

static void setOriginPos(Rectangle* origin, int *currentFrame, int* textureWidth) {
    int amountFramesX = *textureWidth / origin->width;
    origin->y = (int)((*currentFrame - 1) / amountFramesX ) * origin->height;
    origin->x = (int)(*currentFrame - 1 - ((*currentFrame / amountFramesX) * amountFramesX)) * origin->width;
}
