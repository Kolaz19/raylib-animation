#include "animation.h"
#include "include/raylib.h"

static void setOrigin(Rectangle* origin, int *currentFrame, Spritesheet* spriteSheet);
void applyFlip(Animation* animation, FlipAxis axis);

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

void setShiftValues(Animation* animation, float shiftValueX, float shiftValueY) {
    animation->flipShiftX = shiftValueX;
    animation->flipShiftY = shiftValueY;
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
    setOrigin(&animation.origin, &animation.currentFrame, animation.spriteSheet);

    return animation;
}

void startAnimation(Animation* animation) {
    animation->isPlaying = true;
    animation->currentFrame = animation->startFrame;
    animation->advancedTime = 0;
    setOrigin(&animation->origin, &animation->currentFrame, animation->spriteSheet);
    if (animation->flipX == true) {
	applyFlip(animation, FLIPX);
    }
    if (animation->flipY == true) {
	applyFlip(animation, FLIPY);
    }
}

void stopAnimation(Animation* animation) {
    animation->isPlaying = false;
    animation->currentFrame = animation->startFrame;
    animation->advancedTime = 0;
    setOrigin(&animation->origin, &animation->currentFrame, animation->spriteSheet);
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

void flip(Animation* animation, FlipAxis axis) {
    //Flip was already applied
    if ((axis == FLIPX && animation->flipX == true)
	|| (axis == FLIPY && animation->flipY == true)) {
	return;
    }

    if (axis == FLIPX) {
	animation->flipX = true;
    } else {
	animation->flipY = true;
    }
    applyFlip(animation, axis);
}

void flipReset(Animation* animation, FlipAxis axis) {
    //Flip is not applied
    if ((axis == FLIPX && animation->flipX == false)
	|| (axis == FLIPY && animation->flipY == false)) {
	return;
    }

    if (axis == FLIPX) {
	animation->flipX = false;
    } else {
	animation->flipY = false;
    }
    setOrigin(&animation->origin, &animation->currentFrame, animation->spriteSheet);
}

void applyFlip(Animation* animation, FlipAxis axis) {
    if (axis == FLIPX) {
	animation->origin.width *= -1;
	animation->origin.x += animation->flipShiftX;
    } else {
	animation->origin.height *= -1;
	animation->origin.y += animation->flipShiftY;
    }
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
	setOrigin(&animation->origin, &animation->currentFrame, animation->spriteSheet);
	if (animation->flipX == true) {
	    applyFlip(animation, FLIPX);
	}
	if (animation->flipY == true) {
	    applyFlip(animation, FLIPY);
	}
    }
}

void drawAnimation(Animation* animation, Rectangle* destination, Vector2* origin, float rotation) {
    if (!animation->isPlaying) {
	return;
    }

    DrawTexturePro(animation->spriteSheet->texture, animation->origin, *destination, *origin, rotation,  WHITE);
}

static void setOrigin(Rectangle* origin, int *currentFrame, Spritesheet* spriteSheet) {
    origin->width =  (int)(spriteSheet->texture.width / spriteSheet->amountFramesX);
    origin->height =  (int)(spriteSheet->texture.height / spriteSheet->amountFramesY);
    origin->y = (int)((*currentFrame - 1) / spriteSheet->amountFramesX ) * origin->height;
    origin->x = (int)(*currentFrame - 1 - ((*currentFrame / spriteSheet->amountFramesX) * spriteSheet->amountFramesX)) * origin->width;
}
