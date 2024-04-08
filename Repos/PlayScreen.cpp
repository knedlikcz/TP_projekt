#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mStars = BackgroundStars::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.85f, Graphics::Instance()->SCREEN_HEIGHT * 0.05f));
	
	mStartLabel = new Texture("READY", "Minecraft.ttf", 48, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = NULL;

	Enemy::CreatePaths();
	Wasp::CreateDivePaths();
	Butterfly::CreateDivePaths();
	Boss::CreateDivePaths();
}

PlayScreen::~PlayScreen() {
	mTimer = NULL;
	mInput = NULL;

	mStars = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	
	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	mPlayer->Active(false);
	
	mStars->Scroll(false);

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Score\\Score.xml");
	Scores.LoadFile(fullPath.c_str());

	HScore = Scores.FirstChildElement("Scores")->FirstChildElement()->IntAttribute("value");
	
	mSideBar->SetHighScore(HScore);
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetPlayerOneScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	
	mCurrentStage = 0;
}

bool PlayScreen::GameOver() {
	if (!mLevelStarted)
		return false;
	else
		return (mLevel->State() == Level::gameover);
}

void PlayScreen::HandleHighScore() {
	if (mPlayer->Score() > HScore)
	{
		int mScoreToSave = mPlayer->Score();
		std::string fullPath = SDL_GetBasePath();
		
		fullPath.append("Score\\Score.xml");
		Scores.LoadFile(fullPath.c_str());
		Scores.FirstChildElement("Scores")->FirstChildElement()->SetAttribute("value", mScoreToSave);
		Scores.SaveFile(fullPath.c_str());

		mSideBar->SetHighScore(mPlayer->Score());
	}
}

void PlayScreen::Update() {

	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
	}
	else {
		std::chrono::seconds dura(5);
		std::this_thread::sleep_for(dura);
		mGameStarted = true;
	}

	if (mGameStarted) {
		if (mCurrentStage > 0)
			mSideBar->Update();
		
		if (mLevelStarted) {
			mLevel->Update();

			if (mLevel->State() == Level::finished) {
				mLevelStarted = false;
			}
		}
		mPlayer->Update();
		mSideBar->SetPlayerOneScore(mPlayer->Score());
		HandleHighScore();
	}
}

void PlayScreen::Render() {


	
	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted) {

		if (mLevelStarted)
			mLevel->Render();

		mPlayer->Render();
	}

	mSideBar->Render();
	
}