#include "Graphics.h"
#include "AEEngine.h"

//EXAMPLE VARIABLES, NOT STRICTLY NEEDED
static AEGfxVertexList*	pMesh2;				// Pointer to Mesh (Model)
static AEGfxTexture *pTex1;					// Pointer to Texture (Image)
static AEGfxTexture *pTex2;					// Pointer to Texture (Image)

static Sprite* sprite; //only one for debug purposes
static Animation* animtest;
static Animation* animtest2;
//EXAMPLE CODE ENDS HERE

void LevelLoad()
{
  GInitialize();
  pMesh2 = GCreateMesh(128.f, 128.f, 16);

  // Texture 1: From file
  pTex1 = GCreateTexture("PlanetTexture.png");
  pTex2 = GCreateTexture("spiderwolfbrighter.png");

  AEGfxSetBackgroundColor(1.0f, 1.0f, 1.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);
  //EXAMPLE ENDS HERE





  //EXAMPLE CODE, REMOVE OUT WHEN USING
  {
    //sprite = GCreateSprite(-5, -5, pTex1, pMesh2);
    //sprite = GCreateSprite(-25, -25, pTex2, pMesh2);
    animtest = GCreateAnimation(16, pTex2, pMesh2);
    animtest2 = GCreateAnimation(1, pTex1, pMesh2);
    //sprite = GCreateSprite(0, 30, animtest, 4);
    //sprite = GCreateSprite(0, 20, animtest, 4);
    //sprite = GCreateSprite(0, -30, animtest, 4);
    sprite = GCreateSprite(0, 40, animtest2, 4);
    sprite = GCreateSprite(0, 0, animtest, 4);
    //sprite = GCreateHudSprite(0, 0, animtest2, 1);
  }
  //EXAMPLE CODE ENDS HERE
}

void LevelUnload()
{
  GFree();
}