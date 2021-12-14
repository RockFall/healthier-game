#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	SoundEngine = createIrrKlangDevice();

	if (!SoundEngine)
		std::cout << "SOUNDPLAYER: SoundEngine could not be created.\n" << std::endl;
}

SoundPlayer::~SoundPlayer()
{
	SoundEngine->drop();
}

void SoundPlayer::Play(std::string fileName, bool isLoop, float volume)
{
	ISound* sound = SoundEngine->play2D(fileName.c_str(), isLoop, false, true);
	if (sound)
		sound->setVolume(volume);
	else
		std::cout << "SOUNDPLAYER:Play() -- *sound was nullptr" << std::endl;
}

void SoundPlayer::StopAll()
{
	SoundEngine->stopAllSounds();
}
