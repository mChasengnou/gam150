/******************************************************************
Author        :  Matt Chasengnou
File          :  Audio.c
Created       :  1/25/16
Description   :  Provides functionality for working with audio
ChangeLog
-
-
******************************************************************/
#include "Audio.h"
#include "FMOD\fmod.h"
#include <stdlib.h>  /* malloc, free */

/* 
  Initialize the audio system. Instructions for initialization taken
  FMOD site:
http://www.fmod.org/docs/content/generated/FMOD_System_Init.html
*/
void InitializeAudio(void)
{
  /* Create a system object to use with FMOD.  */
  FMOD_SYSTEM *fMod_sysObject = malloc(sizeof(fMod_sysObject));

  /* Max number of audio channels to use. Limit is 4093. */
  int channels = 10;

  void *extraDriverData = NULL;

  /* Create an FMOD system. */
  FMOD_System_Create(&fMod_sysObject);

  /* Initialize the FMOD system. */
  //FMOD_System_Init(fMod_sysObject, channels, )
}