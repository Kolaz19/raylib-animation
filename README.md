# Spritesheet animations in raylib

## Overview

This adds spritesheet animations to raylib.
There are two types of animations.

### LOOP

These animations will start again at the first animation frame when the last frame was reached. 
It will not stop unless we call function `disableAnimation()` or `stopAnimation()`.
This animation is active/enabled from the moment it is created.

### PLAY_ONCE

These animations have to be triggered manually with `startAnimation()`.
If the last frame in the animation was reached, it will stop.
This animation is inactive/disabled from the moment it is created.

## Flipping animations

Because some sprites are not centered on their frames, we have to manually set shift values in order to render the flipped frames at the correct spot.
We can use function `setShiftValues()` for that.

## Usage

Just put animation.c and animation.c in your project or build static library in Makefile with `make buildlib`.
For an example usage, look into main.c.

## Credits

The [spritesheet](https://clembod.itch.io/bringer-of-death-free) in the example comes from [Clembod](https://clembod.itch.io).
