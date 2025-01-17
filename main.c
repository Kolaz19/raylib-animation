#include "include/animation.h"
#include "include/raylib.h"

#define SHIFT_VALUE_X 104
#define SHIFT_VALUE_Y 0
#define MOVEMENT_SPEED 4
#define NO_ANIMATIONS 7

#define movL IsKeyDown(KEY_A)
#define movR IsKeyDown(KEY_D)

void movePlayer(Rectangle *rect);
bool isPlayOnceAnimationPlaying(Animation **animations);

int main(void) {
    InitWindow(1920 * 0.8, 1080 * 0.8, "Example");
    SetTargetFPS(60);

    // First, load spritesheet
    // There can be no animation without spritesheet
    Spritesheet sheet = anim_loadSpritesheet("Bringer-of-Death-SpriteSheet.png", 8, 8);

    // Create animations with this one spritesheet
    // Every animation that is type LOOP is enabled from beginning
    // so we disable walk animation manually
    Animation animIdle = anim_createAnimation(&sheet, 1, 8, 0.06, LOOP);
    Animation animWalk = anim_createAnimation(&sheet, 9, 16, 0.06, LOOP);
    anim_disableAnimation(&animWalk);
    Animation animAttack = anim_createAnimation(&sheet, 17, 26, 0.07, PLAY_ONCE);
    Animation animHurt = anim_createAnimation(&sheet, 27, 29, 0.07, PLAY_ONCE);
    Animation animDeath = anim_createAnimation(&sheet, 30, 39, 0.07, PLAY_ONCE);
    Animation animCast = anim_createAnimation(&sheet, 40, 48, 0.10, PLAY_ONCE);
    Animation animSpell = anim_createAnimation(&sheet, 49, 64, 0.07, PLAY_ONCE);
    Animation *anim[] = {&animIdle, &animWalk, &animAttack, &animHurt,
                         &animDeath, &animCast, &animSpell};

    Rectangle rectPlayer = {600, 400, animIdle.origin.width * 1.5, animIdle.origin.height * 1.5};
    Vector2 origin = {158, 90};

    // If you look at the texture, the frames have an offset
    // This is important when flipping the textures
    for (int i = 0; i < NO_ANIMATIONS - 1; i++) {
        anim_setShiftValues(anim[i], SHIFT_VALUE_X, SHIFT_VALUE_Y);
    }

    while (!WindowShouldClose()) {

        if (movR) {
            for (int i = 0; i < NO_ANIMATIONS - 1; i++)
                anim_flip(anim[i], FLIPX);
        } else if (movL) {
            for (int i = 0; i < NO_ANIMATIONS - 1; i++)
                anim_flipReset(anim[i], FLIPX);
        }

        if (IsKeyPressed(KEY_F)) {
            // Because attack animation is from type PLAY_ONCE
            // we just trigger it here
            anim_startAnimation(&animAttack);
        }

        // Every time a PLAY_ONCE animation is playing
        // we disable all LOOP animations
        if (!isPlayOnceAnimationPlaying(anim)) {
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                anim_enableAnimation(&animWalk);
                anim_disableAnimation(&animIdle);
            } else {
                anim_enableAnimation(&animIdle);
                anim_disableAnimation(&animWalk);
            }
        } else {
            anim_disableAnimation(&animWalk);
            anim_disableAnimation(&animIdle);
        }

        // Disable movement when player is attacking
        if (!isPlayOnceAnimationPlaying(anim))
            movePlayer(&rectPlayer);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 7; i++) {
            anim_drawAnimation(anim[i], &rectPlayer, &origin, 0);
        }
        EndDrawing();

        // You can advance the animation after drawing
        // or before you enable or disable animations
        for (int i = 0; i < 7; i++) {
            anim_advanceAnimation(anim[i]);
        }
    }
    anim_unloadSpritesheet(&sheet);
    CloseWindow();

    return 0;
}

void movePlayer(Rectangle *rect) {
    if (movL) {
        rect->x -= MOVEMENT_SPEED;
    } else if (movR) {
        rect->x += MOVEMENT_SPEED;
    }
}

bool isPlayOnceAnimationPlaying(Animation **animations) {
    for (int i = 0; i < NO_ANIMATIONS; i++) {
        if (animations[i]->type == PLAY_ONCE && animations[i]->isPlaying) {
            return true;
        }
    }
    return false;
}
