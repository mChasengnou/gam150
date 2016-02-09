/******************************************************************
Author        :  Matt Chasengnou
File          :  Audio.c
Created       :  1/25/16
Description   :  Provides functionality for working with audio
ChangeLog
  -2/3/16     : Added LoadSoundSample, LoadSoundStream, PlaySound,
                and StopSound functions.
-
******************************************************************/
#include "Audio.h"
#include <fmod.h>
#include <fmod_common.h>
#include <fmod_errors.h>

#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* strcat */
/*-----------------------------------------------------
DEFINES
-----------------------------------------------------*/
#define true 1
#define false 0
#define TRUE true
#define FALSE false

#define SOUND_FOLDER_NAME "../sounds/"
#define PATH_MAX_LEN 256 /* Maximum number of char allowed in path */
/*-----------------------------------------------------
END DEFINES
------------------------------------------------------*/


/*------------------------------------------------------
GLOBAL VARIABLES
------------------------------------------------------*/
FMOD_SYSTEM              *fmodSystem = NULL;
FMOD_SOUND               *sound;
FMOD_CHANNEL             *channel = 0;
FMOD_RESULT               result;
unsigned int              version;
void                     *extraDriverData = 0;
/*------------------------------------------------------
END GLOBAL VARIABLES
------------------------------------------------------*/


/* 
  Initialize the audio system. Instructions for initialization taken
  FMOD site:
http://www.fmod.org/docs/content/generated/FMOD_System_Init.html
*/
void InitializeAudio(void)
{
  /* Max number of audio channels to use. Limit is 4093. */
  int channels = 32;

  /* Create an FMOD system. */
  result = FMOD_System_Create(&fmodSystem);
  FMOD_ErrorString(result);

  /* check the version. */
  result = FMOD_System_GetVersion(&fmodSystem, &version);
  FMOD_ErrorString(result);

  /* If not the correct version, fatal error is thrown. */
  //if (version < FMOD_VERSION)
  //{
  //  Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
  //}

  /* Initialize the FMOD system. */
  result = FMOD_System_Init(fmodSystem, channels, FMOD_INIT_NORMAL, extraDriverData);
  /* Check for errors. */
  FMOD_ErrorString(result);
}

/*
Closes the audio system and frees it from memory.
*/
void FreeAudio(void)
{
  FMOD_System_Release(fmodSystem);
  FMOD_System_Close(fmodSystem);
}

/*
  Loads a sound as a sample from a file.
  Include extensions in name. ex: "drums.wav"
  pSound is pointer to the sound object you will store the sound in.
*/
void LoadSoundSample(const char *sName, FMOD_SOUND *pSound)
{
  /* Generate the path for the sound file. */
  char *path = (char *)calloc(PATH_MAX_LEN, sizeof(char));

  strcat(path, SOUND_FOLDER_NAME);
  strcat(path, sName);

  result = FMOD_System_CreateSound(fmodSystem, path, FMOD_OPENMEMORY, FMOD_DEFAULT, &pSound);
  FMOD_ErrorString(result);
  
}

// WORRY LATER ABOUT THIS
///*
//  Loads a sound as a stream.
//  Include extensions in name. ex: "drums.wav"
//  pSound is pointer to the sound object you will store the sound in.
//*/
//void LoadSoundStream(const char *pathName, FMOD_SOUND *pSound)
//{
//  result = FMOD_System_CreateStream(fmodSystem, pathName, FMOD_OPENMEMORY, &exinfo, &pSound);
//  FMOD_ErrorString(result);
//}

/*
  Plays a sound.
  pSound is pointer to sound you want to play.
*/
void PlayAudio(FMOD_SOUND *pSound)
{
  result = FMOD_System_PlaySound(fmodSystem, &pSound, 0, false, &channel);
  FMOD_ErrorString(result);
}

/* 
  Stops playback of a sound.
*/
void StopSound(FMOD_SOUND *pSound)
{
  result = FMOD_System_PlaySound(fmodSystem, &pSound, 0, true, &channel);
  FMOD_ErrorString(result);
}

