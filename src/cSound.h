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

	typedef unsigned int tSoundId;

	void Init();
	void Update();
	void Release();

	tSoundId LoadSound(const std::string&);
	void PlayGameSound(tSoundId aIdSound, bool aLoop = false);
	void PauseSound(tSoundId aIdSound);
	void ToggleSound(tSoundId aIdSound);
	void SetVolumeSound(tSoundId aIdSound, float aVolume);

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
	sSound GetSound(tSoundId aIdSound) const;
	void AssingChanelToSound(tSoundId aIdSound, FMOD::Channel* aChannel);

	static FMOD::System* mFMODSystem;

	tSoundId mNewId;
	typedef std::map<tSoundId, sSound> tSoundMap;
	tSoundMap mSounds;
};

#endif