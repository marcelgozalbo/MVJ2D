#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>
#include <map>
#include "fmod.hpp"

class cSound
{
public:
	cSound();
	~cSound();

	void Init();
	void Update();
	void Release();

	unsigned int LoadSound(const std::string&);
	void PlayGameSound(unsigned int aIdSound, bool aLoop = false);
	void PauseSound(unsigned int aIdSound);
	void ToggleSound(unsigned int aIdSound);
	void SetVolumeSound(unsigned int aIdSound, float aVolume);

private:

	struct sSound
	{
		FMOD::Sound*	Sound;
		FMOD::Channel*	Channel;

		sSound();
		sSound(FMOD::Sound* aSound, FMOD::Channel* aChannel);
		inline bool operator==(const sSound& aSound){ return Sound == aSound.Sound; };
	};

	bool CheckError(std::string aFunctionName, FMOD_RESULT aResult);
	sSound GetSound(unsigned int aIdSound) const;
	void AssingChanelToSound(unsigned int aIdSound, FMOD::Channel* aChannel);

	static FMOD::System* mFMODSystem;

	unsigned int mNewId;
	typedef std::map<unsigned int, sSound> tSoundMap;
	tSoundMap mSounds;
};

#endif