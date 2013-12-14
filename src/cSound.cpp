#include "cSound.h"
#include <iostream>
#include "fmod_errors.h"
#include "cLog.h"
#include <sstream>


cSound::sSound::sSound() :
	Sound(NULL), Channel(NULL)
{
}

cSound::sSound::sSound(FMOD::Sound* aSound, FMOD::Channel* aChannel) :
	Sound(aSound), Channel(aChannel)
{
}

FMOD::System* cSound::mFMODSystem = NULL;

cSound::cSound() :
mNewId(0)
{
	Init();
}

cSound::~cSound()
{
	Release();
}

void cSound::Init()
{
	FMOD_RESULT result = FMOD::System_Create(&mFMODSystem);
	if (CheckError("System_Create", result))
	{
		return;
	}
	result = mFMODSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	if (CheckError("init", result))
	{
		return;
	}
}

void cSound::Update()
{
	if (mFMODSystem)
	{
		mFMODSystem->update();
	}
}

void cSound::Release()
{
	if (mFMODSystem)
	{
		mFMODSystem->release();
	}
}

cSound::tSoundId cSound::LoadSound(const std::string& aSoundName)
{
	tSoundId identifier = -1;
	FMOD::Sound* sound = nullptr;
	FMOD_CREATESOUNDEXINFO settings;
	settings.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	memset(&settings, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	FMOD_RESULT result = mFMODSystem->createSound(aSoundName.c_str(), FMOD_DEFAULT, nullptr, &sound);
	if (!CheckError( (std::string("LoadSound '") + aSoundName + "' ") , result))
	{
		identifier = mNewId++;
		mSounds[identifier] = sSound(sound, nullptr);
	}
	return identifier;
}

void cSound::PlayGameSound(tSoundId aIdSound, bool aLoop)
{
	sSound sound = GetSound(aIdSound);
	if (sound.Sound)
	{
		mFMODSystem->playSound(sound.Sound, nullptr, false, &sound.Channel);
		AssingChanelToSound(aIdSound, sound.Channel);
		if (aLoop)
			sound.Channel->setLoopCount(-1);
	}
}

void cSound::PauseSound(tSoundId aIdSound)
{
	sSound sound = GetSound(aIdSound);
	if (sound.Sound && sound.Channel)
	{
		sound.Channel->setPaused(true);
	}
}

void cSound::ToggleSound(tSoundId aIdSound)
{
	sSound sound = GetSound(aIdSound);
	if (sound.Sound && sound.Channel)
	{
		bool paused = true;
		sound.Channel->getPaused(&paused);
		sound.Channel->setPaused(!paused);
	}
}

void cSound::SetVolumeSound(tSoundId aIdSound, float aVolume)
{
	sSound sound = GetSound(aIdSound);
	if (sound.Sound && sound.Channel)
	{
		sound.Channel->setVolume(aVolume);
	}
}

bool cSound::CheckError(std::string aFunctionName, FMOD_RESULT aResult)
{
	bool returnValue = false;
	if (aResult != FMOD_OK)
	{
		std::stringstream message;
		message << "cSound: FMOD '" << aFunctionName << "' error: (" << aResult << ") " << FMOD_ErrorString(aResult) << std::endl;
		cLog::Instance()->Msg(message.str());
		returnValue = true;
	}
	return returnValue;
}

cSound::sSound cSound::GetSound(tSoundId aIdSound) const
{
	sSound returnValue;
	tSoundMap::const_iterator it = mSounds.find(aIdSound);
	if (it != mSounds.end())
	{
		returnValue = it->second;
	}
	return returnValue;
}

void cSound::AssingChanelToSound(tSoundId aIdSound, FMOD::Channel* aChannel)
{
	tSoundMap::iterator it = mSounds.find(aIdSound);
	if (it != mSounds.end())
	{
		it->second.Channel = aChannel;
	}
}
