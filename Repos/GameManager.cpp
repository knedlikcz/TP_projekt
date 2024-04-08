#include "GameManager.h"
#include <time.h>
namespace QuickSDL {
	GameManager* GameManager::sInstance = NULL;

	GameManager* GameManager::Instance() {

		if(sInstance == NULL)
			sInstance = new GameManager();

		return sInstance;
	}

	void GameManager::Release() {

		delete sInstance;
		sInstance = NULL;
	}

	GameManager::GameManager() {
		srand(time(0));

		mQuit = false;

		mGraphics = Graphics::Instance();

		if(!Graphics::Initialized())
			mQuit = true;

		mAssetMgr = AssetManager::Instance();

		mInputMgr = InputManager::Instance();

		mAudioMgr = AudioManager::Instance();

		mTimer = Timer::Instance();

		mPhysMgr = PhysicsManager::Instance();
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile | PhysicsManager::CollisionFlags::HostileProjectiles);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Hostile);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectiles);
		mPhysMgr->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectiles, PhysicsManager::CollisionFlags::Friendly);

		mScreenMgr = ScreenManager::Instance();
	}

	GameManager::~GameManager() {

		ScreenManager::Release();
		mScreenMgr = NULL;

		PhysicsManager::Release();
		mPhysMgr = NULL;

		AudioManager::Release();
		mAudioMgr = NULL;

		AssetManager::Release();
		mAssetMgr = NULL;

		Graphics::Release();
		mGraphics = NULL;

		InputManager::Release();
		mInputMgr = NULL;

		Timer::Release();
		mTimer = NULL;

	}

	void GameManager::EarlyUpdate() {

		mInputMgr->Update();
	}

	void GameManager::Update() {

		mScreenMgr->Update();
	}

	void GameManager::LateUpdate() {

		mPhysMgr->Update();
		mInputMgr->UpdatePrevInput();
		mTimer->Reset();
	}

	void GameManager::Render() {

		mGraphics->ClearBackBuffer();

		mScreenMgr->Render();

		mGraphics->Render();
	}

	void GameManager::Run() {

		while(!mQuit) {

			mTimer->Update();

			while(SDL_PollEvent(&mEvents) != 0) {

				if(mEvents.type == SDL_QUIT) {

					mQuit = true;
				}
			}

			if(mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

				EarlyUpdate();
				Update();
				LateUpdate();
				Render();
			}
		}
	}
}