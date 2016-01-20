#include "Graphics.h"
#include "AEEngine.h"



//EXAMPLE VARIABLES, NOT STRICTLY NEEDED
static AEGfxVertexList*	pMesh2;				// Pointer to Mesh (Model)
static AEGfxTexture *pTex1;					// Pointer to Texture (Image)
static AEGfxTexture *pTex2;					// Pointer to Texture (Image)

static Sprite* sprite; //only one for debug purposes
SpriteList* spriteList;


Animation* animtest;
Animation* animtest2;
//EXAMPLE CODE ENDS HERE

/*!
\brief Initializes graphics stuff.
*/
void GInitialize()
{
  //create sprite list
  spriteList = malloc(sizeof(SpriteList));
  spriteList->first = NULL;
  spriteList->last = NULL;

  //EXAMPLE IMAGE/MESH LOADING & CREATION
  // Informing the library that we're about to start adding triangles
  AEGfxMeshStart();

  // This shape has 2 triangles
  AEGfxTriAdd(
    -64.0f, -64.0f, 0x00FF00FF, 0.0f, 1.0f,
    64.0f, -64.0f, 0x00FFFF00, 0.0625f, 1.0f,
    -64.0f, 64.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    64.0f, -64.0f, 0x00FFFFFF, 0.0625f, 1.0f,
    64.0f, 64.0f, 0x00FFFFFF, 0.0625, 0.0f,
    -64.0f, 64.0f, 0x00FFFFFF, 0.0f, 0.0f);

  pMesh2 = AEGfxMeshEnd();
  AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");


  // Texture 1: From file
  pTex1 = AEGfxTextureLoad("PlanetTexture.png");
  AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

  pTex2 = AEGfxTextureLoad("spiderwolfbrighter.png");

  AEGfxSetBackgroundColor(1.0f, 1.0f, 1.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);
  //EXAMPLE ENDS HERE
  




    //EXAMPLE CODE, REMOVE OUT WHEN USING
  {
    //sprite = CreateSprite(-5, -5, pTex1, pMesh2);
    //sprite = CreateSprite(-25, -25, pTex2, pMesh2);
    animtest = CreateAnimation(16, pTex2, pMesh2);
    animtest2 = CreateAnimation(1, pTex1, pMesh2);
    sprite = CreateSprite(0, 30, animtest, 4);
    sprite = CreateSprite(0, 20, animtest, 4);
    sprite = CreateSprite(0, -30, animtest, 4);
    sprite = CreateSprite(0, 50, animtest, 4);
    sprite = CreateSprite(10, 60, animtest, 4);
  }
    //EXAMPLE CODE ENDS HERE
}

/*!
\brief Call function every frame to render graphics.
*/
void GRender()
{
    //EXAMPLE CODE, REMOVE OUT WHEN USING
  {
    sprite->y -= 1;
    SortSprite(sprite, -1);
  }
    //EXAMPLE CODE ENDS HERE



  AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
  //render sprites in list starting from the first item
  if (spriteList->first)
  {
    Sprite* spriteIndex = spriteList->first;
    while (spriteIndex)
    {
      SimAnimation(spriteIndex);
      AEGfxSetPosition(spriteIndex->x, spriteIndex->y);
      AEGfxTextureSet(spriteIndex->animation->texture, spriteIndex->animation->frameOffset * spriteIndex->frame, 0.0f);
      AEGfxSetTransparency(1.0f);
      AEGfxMeshDraw(spriteIndex->animation->mesh, AE_GFX_MDM_TRIANGLES);
      spriteIndex = spriteIndex->lowerSprite;


    }
  }

  
  
}

/*!
\brief Call this function to unload everything once the gameplay is over.
*/
void GFree()
{
  // Freeing the objects and textures
  AEGfxMeshFree(pMesh2);

  AEGfxTextureUnload(pTex1);
}

/*!
\brief creates sprite with given parameters
Sprite layer is initialized based on _spriteY param.

\param _spriteX is the x position of the created sprite
\param _spriteY is the y position of the created sprite
\param _texture is a pointer to what texture for the sprite
\param _mesh is a pointer to the vertex list (mesh) for the sprite
\param _frameDelay the number of frames to wait in between changing frames for the animation
*/
Sprite* CreateSprite(float _spriteX, float _spriteY, Animation* _animation, float _frameDelay)//struct AEGfxTexture* _texture, struct AEGfxVertexList* _mesh)
{
 
  Sprite* newSprite = malloc(sizeof(struct Sprite));
  newSprite->x = _spriteX;
  newSprite->y = _spriteY;
  //newSprite->texture = _texture;
  //newSprite->mesh = _mesh;
  newSprite->higherSprite = NULL;
  newSprite->lowerSprite = NULL;
  newSprite->animation = _animation;
  newSprite->frame = 0;
  newSprite->timer = 0;
  newSprite->paused = 0;
  newSprite->frameDelay = _frameDelay;


  if (!spriteList->first) //if first, set first in list
  {
    spriteList->first = newSprite;
  }
  else 
  { 
    //otherwise, sort through the list until the correct y position is found for layering, and insert self there

    Sprite* index = spriteList->first;


    if (newSprite->y > index->y) //if higher than currently highest object, take place as first in list
    {
      spriteList->first = newSprite;
      newSprite->lowerSprite = index;
      index->higherSprite = newSprite;
    }
    else 
    {
      //starting from the top, go down the spritelist until the appropriate sprite layer can be found
      
      while (index->lowerSprite && index->lowerSprite->y > _spriteY)
      {
        index = index->lowerSprite;
      }
      if (index->lowerSprite)
      {
        index->lowerSprite->higherSprite = newSprite;
        newSprite->lowerSprite = index->lowerSprite;
      }
      index->lowerSprite = newSprite;
      newSprite->higherSprite = index;
      
    }
  }
  return newSprite;
}

/*!
\brief Removes sprite object 

\param _input pointer to pointer to sprite
*/
void RemoveSprite(Sprite** _input)
{
  if (_input)
  {
    //printf("inp: %p", _input);
    if ((*_input)->higherSprite)
    {
      if ((*_input)->lowerSprite)
      {
        (*_input)->lowerSprite->higherSprite = (*_input)->higherSprite;
        (*_input)->higherSprite->lowerSprite = (*_input)->lowerSprite;
      }
      else
      {
        (*_input)->higherSprite->lowerSprite = NULL;
        spriteList->last = (*_input)->higherSprite;
      }

    }
    else
    {
      if ((*_input)->lowerSprite)
      {
        (*_input)->lowerSprite->higherSprite = NULL;
        spriteList->first = (*_input)->lowerSprite;
      }
      else
      {
        spriteList->first = NULL;
        spriteList->last = NULL;
      }
    }
    free(*_input); //note: may also free animation? no time to test, will check later
    *_input = NULL;
  }
}


/*!
\brief Generates an animation from an image file with specified info.
Does not create texture & mesh objects as part of the process.

\param _numFrames the total number of frames in the animation
\param _texture pointer to the texture to be used
\param _mesh pointer to the mesh to be used
*/
Animation* CreateAnimation(float _numFrames, struct AEGfxTexture* _texture, struct AEGfxVertexList* _mesh)
{
  Animation* newAnim = malloc(sizeof(Animation));
  
  newAnim->length = _numFrames;
  newAnim->frameOffset = 1 / _numFrames;
  
  newAnim->texture = _texture;
  newAnim->mesh = _mesh;
  return newAnim;
}

/*!
\brief Call to simulate animation (changing frames)

\param _input pointer to sprite
*/
void SimAnimation(Sprite* _input)
{
  if (!(_input->paused))
  {
    ++_input->timer; //only increment if not paused
  }
  if (_input->frameDelay <= _input->timer)
  {
    ++_input->frame;
    _input->timer = 0;
    
  }
  if (_input->frame >= _input->animation->length)
  {
    _input->frame = 0;
    printf("a");

  }
}
/*!
\brief sorts sprite layer according to y position
Call this function when a sprite changes y position to make sure it is layered correctly. 
I'm aware that the loop could probably be optimized way better. It kept breaking on me, so I went overkill on safety checks ok? D:

\param _sprite input sprite object
\param _direction y direction of change
*/
void SortSprite(Sprite* _sprite, float _direction)
{
  if (_direction > 0) //assuming that the sprite is going upwards:
  {

    if (_sprite->higherSprite && spriteList->first != _sprite) //if not at the top...
    {

      Sprite* oldHigher; //old higher sprite to be swapped
      
      //keep moving self up through list until the highest object has a higher y value than the sprite
      while (_sprite->higherSprite && _sprite->higherSprite->y < _sprite->y) 
      {

        oldHigher = _sprite->higherSprite;
        
        if (_sprite->lowerSprite)
        {
          _sprite->lowerSprite->higherSprite = oldHigher;
          oldHigher->lowerSprite = _sprite->lowerSprite;
        }
        else 
        {
          //if the sprite was the lowest before, update that fact with the new lowest sprite
          oldHigher->lowerSprite = NULL;
          spriteList->last = oldHigher;
        }

        _sprite->lowerSprite = oldHigher;

        if (oldHigher->higherSprite)
        {
          _sprite->higherSprite = oldHigher->higherSprite;
          oldHigher->higherSprite->lowerSprite = _sprite;
          oldHigher->higherSprite = _sprite;
        }
        else 
        {
          
          _sprite->higherSprite = NULL;
          oldHigher->higherSprite = _sprite;
          spriteList->first = _sprite;
          break;
        }
        
      }
      
    }

  }
  else if(_direction < 0) //same process, but going downwards instead of upwards
  {
    if (_sprite->lowerSprite && spriteList->last != _sprite) 
    {

      Sprite* oldLower; 
      while (_sprite->lowerSprite && _sprite->lowerSprite->y > _sprite->y)
      {

        oldLower = _sprite->lowerSprite;
        if (_sprite->higherSprite)
        {
          _sprite->higherSprite->lowerSprite = oldLower;
          oldLower->higherSprite = _sprite->higherSprite;
        }
        else 
        {
          oldLower->higherSprite = NULL;
          spriteList->first = oldLower;
        }

        _sprite->higherSprite = oldLower;

        if (oldLower->lowerSprite)
        {
          _sprite->lowerSprite = oldLower->lowerSprite;
          oldLower->lowerSprite->higherSprite = _sprite;
          oldLower->lowerSprite = _sprite;
        }
        else 
        {

          _sprite->lowerSprite = NULL;
          oldLower->lowerSprite = _sprite;
          spriteList->last = _sprite;
          break;
        }


      }

    }
  }

}