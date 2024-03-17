#include "animation.h"
#include "include/raylib.h"

Spritesheet LoadSpritesheet(const char* fileName, int frameWidth, int frameHeight) {
    Spritesheet spriteSheet;

    Texture2D texture = LoadTexture(fileName);
    spriteSheet.texture = texture;

    spriteSheet.frameWidth = frameWidth;
    spriteSheet.frameHeight = frameHeight;

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

    return animation;
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
}

void drawAnimation(Animation* animation, float posX, float posY, float width, float height, float originX,float originY, float rotation ) {
    if (!animation->isPlaying) {
	return;
    }

    int amountFramesX = animation->spriteSheet->texture.width / animation->spriteSheet->frameWidth;
    int yPos = (animation->currentFrame - 1) / amountFramesX * animation->spriteSheet->frameHeight;
    int xPos = (animation->currentFrame - 1 - ((animation->currentFrame / amountFramesX) * amountFramesX)) * animation->spriteSheet->frameWidth;
    Rectangle source = { xPos, yPos, animation->spriteSheet->frameWidth, animation->spriteSheet->frameHeight};
    DrawTexturePro(animation->spriteSheet->texture, source, (Rectangle){posX,posY, width,height}, (Vector2) {originX,originY}, rotation,  WHITE);
}
