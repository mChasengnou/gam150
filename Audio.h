/******************************************************************
Author        :  Matt Chasengnou
File          :  Audio.h
Created       :  1/25/16
Description   :  Contains forward declarations used by Audio.c
ChangeLog
  -
  -
******************************************************************/
#pragma once
#ifndef AUDIO_H
#define AUDIO_H

/* Initializes FMod for audio playback. */
void InitializeAudio(void);

void PlaySound();


#endif // !AUDIO_H
