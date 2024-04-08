
#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include "AssetManager.h"

namespace QuickSDL {

	class AudioManager {

	private:
		static AudioManager* sInstance;

		AssetManager* mAssetMgr;

	public:
		static AudioManager* Instance();
		static void Release();

		void PlayMusic(std::string filename, int loops = -1);
		void PauseMusic();
		void ResumeMusic();
		void PlaySFX(std::string filename, int loops = 0, int channel = 0);

	private:

		AudioManager();
		~AudioManager();
	};
}
#endif
