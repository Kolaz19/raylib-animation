#include "animation.h"
#include "include/raylib.h"
#include <stdio.h>

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

void advanceAnimation(Animation* animation) {
    int previousFrame = animation->currentFrame;
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
	    return;
	}
    }
    //Set new origin when current frame has changed
    if (previousFrame != animation->currentFrame) {
	setOriginPos(&animation->origin, &animation->currentFrame, &animation->spriteSheet->texture.width);
    }
}

void drawAnimation(Animation* animation, float posX, float posY, float width, float height, float originX,float originY, float rotation ) {
    if (!animation->isPlaying) {
	return;
    }

    DrawTexturePro(animation->spriteSheet->texture, animation->origin, (Rectangle){posX,posY, width,height}, (Vector2) {originX,originY}, rotation,  WHITE);
}

static void setOriginPos(Rectangle* origin, int *currentFrame, int* textureWidth) {
    int amountFramesX = *textureWidth / origin->width;
    origin->y = (int)((*currentFrame - 1) / amountFramesX ) * origin->height;
    origin->x = (int)(*currentFrame - 1 - ((*currentFrame / amountFramesX) * amountFramesX)) * origin->width;
    printf("X:%f\tY:%f\n",origin->x,origin->y);
}
