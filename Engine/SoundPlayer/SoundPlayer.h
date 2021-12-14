#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <irrklang/irrKlang.h>
#include <string>
#include <iostream>

using namespace irrklang;

// Responsible for playing audio files
class SoundPlayer
{
public:
	// ----- Contructor -----
	SoundPlayer();
	~SoundPlayer();

	// Plays the audio of given file
	void Play(std::string fileName, bool isLoop, float volume = 1);

	// Stop all sounds
	void StopAll();

private:
	ISoundEngine* SoundEngine;
};

#endif

