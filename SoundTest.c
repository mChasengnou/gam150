/******************************************************************
Author        :  Matt Chasengnou
File          :  SoundTest.c
Created       :  2/3/16
Description   :  Tests the sound functions
ChangeLog
-
-
******************************************************************/
#include "Audio.h"
#include "AEEngine.h"
#include "AEInput.h"
#include "fmod.h"

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")

char sPath[] = "sounds\\Sample.ogg";
FMOD_SOUND *sound;

extern FMOD_SYSTEM *fmodSystem;
extern FMOD_CHANNEL *channel;
/*
Tests the sound loading function
*/
void TestAudioLoad()
{
  LoadSoundSample(sPath, sound);
}

/*
Test the playback of sound
*/
void TestAudioPlay()
{
  if (AEInputCheckTriggered('M'))
  {
    PlayAudio(sound);
  }

  FMOD_System_Update(fmodSystem);

  unsigned int ms = 0;
  unsigned int lenms = 0;
  int         playing = 0;
  int         paused = 0;
  int          channelsplaying = 0;

  if (channel)
  {
    FMOD_SOUND *currentsound = 0;

  //  FMOD_Channel_IsPlaying(&channel, &playing);
  ///*  if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
  //  {
  //    ERRCHECK(result);
  //  }*/

  //  result = channel->getPaused(&paused);
  //  if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
  //  {
  //    ERRCHECK(result);
  //  }

  //  result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
  //  if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
  //  {
  //    ERRCHECK(result);
  //  }

    FMOD_Channel_GetCurrentSound(channel, &currentsound);
    if (currentsound)
    {
      FMOD_Sound_GetLength(currentsound, &lenms, FMOD_TIMEUNIT_MS);
   /*   result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
      if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
      {
        ERRCHECK(result);
      }*/
    }
  }
  FMOD_System_GetChannelsPlaying(fmodSystem, &channelsplaying);
}

/*
Runs all testing functions.
*/
void TestAudio()
{
  TestAudioLoad();
  TestAudioPlay();
}