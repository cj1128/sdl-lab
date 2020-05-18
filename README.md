# SDL Lab

Projects built with SDL2 for learning.

All projects are based on [Lazy Foo's SDL tutorial](http://lazyfoo.net/tutorials/SDL/index.php).

## Build

You have to install:

- `SDL2`
- `SDL2_image`
- `SDL2_ttf`
- `SDL2_mixer`

If you are on Mac, just use brew: `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer`.

Each project has a directory and we can use `make [name].out` to build them.

```bash
$ make window.out
# must run projects inside their own directory
$ cd window && ./main.out
# or we can run it with make
$ make window.run
```

## TOC

<!-- MarkdownTOC -->

- [Window](#window)
- [Renderer](#renderer)
- [Viewport](#viewport)
- [PNG](#png)
- [Rect](#rect)
- [Blit Scaled](#blit-scaled)
- [Mouse](#mouse)
- [Keyboard](#keyboard)
- [Keyboard State](#keyboard-state)
- [Frame Rate](#frame-rate)
- [Fixed Frame Rate](#fixed-frame-rate)
- [Timer](#timer)
- [Advanced Timer](#advanced-timer)
- [Alpha Blend](#alpha-blend)
- [Font](#font)
- [Audio](#audio)
- [Color Key](#color-key)
- [Sprite](#sprite)
- [Animation](#animation)
- [Rotate](#rotate)
- [Motion](#motion)
- [Scrolling](#scrolling)
- [Text Input](#text-input)
- [Collision Detection](#collision-detection)
- [Circular Collision Detection](#circular-collision-detection)
- [Multiple Displays](#multiple-displays)
- [Particles](#particles)
- [Texture Manipulation](#texture-manipulation)
- [Gradient](#gradient)

<!-- /MarkdownTOC -->

## Window

Create a simple hello world window and render a BMP with `SDL_UpdateWindowSurface`.

![](http://asset.cjting.cn/FtSrZ_wLOGWklJirBbTKsfrRkPIq.png)

## Renderer

Render using a texture instead of a surface.

## Viewport

We can use `SDL_RenderSetViewport` to set where we want to render.

![](http://asset.cjting.cn/Fj6bxJY_7m4Eo9xlFfP5htjJfsTn.png)

## PNG

Load a PNG file instead of BMP using `SDL_image`.

## Rect

We can use `SDL_RenderFillRect` to draw rectangles.

![](http://asset.cjting.cn/FjLrwydr0NZXsWLtuj1IKVPllH0r.png)

## Blit Scaled

Blit scaled image to window.

## Mouse

We can listen to a bunch of mouse events.

## Keyboard

Simple keyboard handling by processing SDL events.

## Keyboard State

We can also handle keyboard by querying keyboard state with `SDL_GetKeyboardState()`.

## Frame Rate

Display frame rate in the screen.

## Fixed Frame Rate

Lock our frame rate using `SDL_Delay`.

## Timer

A simple timer showing ellapsed milliseconds.

![](http://asset.cjting.cn/FmXP4dUT7kcypnJA_oT-wo8Hsb-H.png)

## Advanced Timer

A sort of advanced timer showing elapsed seconds.

![](http://asset.cjting.cn/FmQdQ6xVeLKFjEttwsOTXwvIKQer.png)

## Alpha Blend

Alpha belnd two pngs.

![](http://asset.cjting.cn/FuD1yGzr2VbxcGvLhnz0XCuE5DrQ.png)


## Font

Let's render some text with `SDL_ttf`.

![](http://asset.cjting.cn/FhW7u7jkypeO3f8EU_2xRvdkXIlc.png)

## Audio

Let's play some music!

NOTE: If you install `sdl2_mixer` with brew, it doesn't support mp3 by default. You have to manually edit the formula and add the mp3 support.

## Color Key

Color key means that we can tell SDL that it shoudl treat some key as transparent.

## Sprite

Display part of a big sprite image.

## Animation

A simple sprite animation.

![](http://asset.cjting.cn/FlNHZURkQqs6vMkr4aBfBv7ogJos.png)


## Rotate

Use `SDL_RenderCopyEx` to rotate our little guy.

![](http://asset.cjting.cn/Fq9gekwKlFQmp81i4xgI8XqiDIs0.png)

## Motion

Let's move our cute rectangle with keyboards.

![](http://asset.cjting.cn/Fgm60aYSsXnj16vx4EnW_z5icl4B.png)

## Scrolling

Let's explore the bigger world.

![](http://asset.cjting.cn/FsEtA84-2cHrRZYVafTlFqXocC3C.png)

## Text Input

By using `SDL_StartTextInput` and listening `SDL_TEXTINPUT` event, we can build a simple text input field.

![](http://asset.cjting.cn/Fmuk0xbcaI1MBN2dXwoyOcue6gd-.png)

## Collision Detection

Detect collision between two rectangles.

![](http://asset.cjting.cn/Fow4LDGn6Cs8yd-SbWglnMuM2UDR.png)

## Circular Collision Detection

Detect collision between two circles.

![](http://asset.cjting.cn/FggB3jYz5PkEGxT8rXWDNK_GRUGc.png)

## Multiple Displays

Switch our window to different monitors.

## Particles

A simple particles system.

![](http://asset.cjting.cn/FoplBXaWc21D8q3ZiCV_DiiNFoEL.png)

## Texture Manipulation

We can get pixels from texture and do whatever we want.

In this demo we manually implement color key functionality.

## Gradient

Create a simple gradient using `SDL_CreateTexture`.

![](http://asset.cjting.cn/Ft7jB7y2mQ-f5G30zdl0uNQVVM_V.png)
