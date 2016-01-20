#pragma once

typedef struct Animation Animation;
typedef struct Sprite Sprite; 
typedef struct SpriteList SpriteList;

/*!
\struct Sprite
\brief Sprite object

Also acts as a linked list between sprites for layering resolution. Sprites are layered with a painter's algorithm (back first), assuming higher Y is further back.
*/
 struct Sprite
{
  //struct AEGfxVertexList* mesh; /*! pointer to the mesh for the sprite*/
  //struct AEGfxTexture* texture; /*! pointer to texture of sprite*/
  struct Animation* animation; /*! pointer to the sprite's animation*/
  float x; /*! x position of sprite*/
  float y; /*! y position of sprite*/
  Sprite* lowerSprite; /*! pointer to the next lowest (lower y position) sprite in the environment*/
  Sprite* higherSprite; /*! pointer to the next highest (higher y position) sprite in the environment*/

  int frame; /*! current frame being played*/
  int timer; /*! internal timer for frame delay calculations*/
  int paused; /*! bool, whether or not to play*/

  int frameDelay; /*! how many engine frames to wait before changing animation frame*/


 };

 
 /*!
 \struct SpriteList
 \brief info for linked list of sprites
 */
 struct SpriteList
 {
   Sprite* first; /*! first sprite in list*/
   Sprite* last; /*! last sprite in list*/
 };


 /*!
 \struct Animation
 \brief contains information about animations
 Note: animation spritesheet should be 1 frame high- all frames on horizontal strip.
 */
 struct Animation
 {
   struct AEGfxVertexList* mesh; /*! pointer to the mesh for the animation*/
   struct AEGfxTexture* texture; /*! pointer to texture of animation*/

   
   int length; /*! length of animation in frames*/
   
   float frameOffset; /*! amount to offset, aka 1/(num frames)*/
 };

void GRender(); //call every frame to render sprites

void GInitialize(); //call before render once to initialize

void GFree(); //call after game/level is over to free resources

Sprite* CreateSprite(float _spriteX, float _spriteY, Animation* _animation, float _frameDelay); //creates a sprite struct

void SortSprite(Sprite* sprite, float direction); //call every time the sprite changes y position

Animation* CreateAnimation(float _numFrames, struct AEGfxTexture* _texture, struct AEGfxVertexList* _mesh); //creates an animation

void SimAnimation(Sprite* _input); //call every frame on every sprite to animate

void RemoveSprite(Sprite** _input); //call to remove a sprite on screen