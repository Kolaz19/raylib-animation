#include "animation.h"

struct Spritesheet {
    Image* image;
    int amountFrames;
    int frameWidth;
    int frameHeight;
};

Spritesheet LoadSpritesheet(const char* fileName, int amountFrames, int frameWidth, int frameHeight) {
    Spritesheet sh;

    Image img = LoadImage(fileName);
    sh.image = &img;

    sh.amountFrames = amountFrames;
    sh.frameWidth = frameWidth;
    sh.frameHeight = frameHeight;

    return sh;
}

void unloadSpritesheet(Spritesheet spriteSheet) {
    UnloadImage(*(spriteSheet.image));
}
