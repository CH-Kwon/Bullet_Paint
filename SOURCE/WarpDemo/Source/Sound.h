#ifndef FMOD_H
#define FMOD_H
#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"

#include <iostream>

typedef FMOD::Sound * SoundClass;

class SoundSystemClass
{
	// Pointer to the FMOD instance
	FMOD_RESULT m_result;
	FMOD::System *m_pSystem;

public:
	SoundSystemClass()
	{
		m_result = FMOD::System_Create(&m_pSystem);

		if (m_result != FMOD_OK)
		{
			// Report Error
			std::cout << "FMOD ERROR CODE: (%d)" << m_result << std::endl;
			std::cout << FMOD_ErrorString(m_result) << std::endl;
			exit(-1);
		}
		int driverCount = 0;
		m_pSystem->getNumDrivers(&driverCount);

		if (driverCount == 0)
		{
			std::cout << "FMOD ERROR CODE: (%d)" << m_result << std::endl;
			std::cout << FMOD_ErrorString(m_result) << std::endl;
			exit(-1);
		}

		// default: 36 channels

		m_result = m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
		if (m_result != FMOD_OK)
		{
			std::cout << "FMOD ERROR CODE: (%d)" << m_result << std::endl;
			std::cout << FMOD_ErrorString(m_result) << std::endl;
			exit(-1);
		}
	}

	void createSound(SoundClass *pSound, const char* pFile)
	{
		m_pSystem->createSound(pFile, FMOD_HARDWARE, 0, pSound);
	}

	//bLoop = Is this sound looping?
	void playSound(SoundClass pSound, bool bLoop = false)
	{
		if (!bLoop) pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1); // play unlimited
		}
		m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
	}

	void releaseSound(SoundClass pSound)
	{
		pSound->release();
	}
};


#endif // FMOD_H