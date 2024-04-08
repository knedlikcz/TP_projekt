
#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "AudioManager.h"
#include "Timer.h"
#include "ScreenManager.h"
#include "PhysicsManager.h"

namespace QuickSDL {

	class GameManager {

	private:
		static GameManager* sInstance;

		const int FRAME_RATE = 120;

		bool mQuit;

		Graphics* mGraphics;
		AssetManager* mAssetMgr;
		InputManager* mInputMgr;
		AudioManager* mAudioMgr;
		PhysicsManager* mPhysMgr;

		Timer* mTimer;

		SDL_Event mEvents;

		ScreenManager* mScreenMgr;
	public:

		static GameManager* Instance();

		static void Release();

		void Run();

	private:
		GameManager();

		~GameManager();

		void EarlyUpdate();

		void Update();

		void LateUpdate();

		void Render();
	};
}

#endif
