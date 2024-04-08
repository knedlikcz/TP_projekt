#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top bar
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", "Minecraft.ttf", 32, { 200, 0, 0 });
	mHiScore = new Texture("Hi-Score", "Minecraft.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new Texture("2UP", "Minecraft.ttf", 32, { 200, 0, 0 });
	mPlayerOneScore = new ScoreBoard();
	mHiScoreBoard = new ScoreBoard();
	mPlayerTwoScore = new ScoreBoard();

	mPlayerOne->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mHiScoreBoard->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);

	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	mHiScore->Pos(Vector2(0.0f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));
	//Scores
	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.25f, 32.0f));
	mHiScoreBoard->Pos(Vector2(0.0f, 32.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.25f, 32.0f));

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Score\\Score.xml");
	Scores.LoadFile(fullPath.c_str());

	HScore = Scores.FirstChildElement("Scores")->FirstChildElement()->IntAttribute("value");
	
	mHiScoreBoard->Score(HScore);
	
	mTopBar->Parent(this);

	//Logo
	mLogo = new Texture("GalagoLogo.png", 0, 0, 360, 180);
	mAnimatedLogo = new AnimatedTexture("GalagoLogo.png", 0, 0, 360, 180, 3, 0.4f, AnimatedTexture::vertical);

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	
	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	//Play mode
	mPlayMode = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayer = new Texture("1 PLAYER", "Minecraft.ttf", 32, { 230, 230, 230 });
	mTwoPlayer = new Texture("2 PLAYER", "Minecraft.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Cursor.png");
	
	mOnePlayer->Parent(mPlayMode);
	mTwoPlayer->Parent(mPlayMode);
	mCursor->Parent(mPlayMode);
	
	mOnePlayer->Pos(Vector2(Vector2(0.0f, -35.0f)));
	mTwoPlayer->Pos(Vector2(Vector2(0.0f, 35.0f)));
	mCursor->Pos(Vector2(Vector2(-120.0f, -40.0f)));
	
	mPlayMode->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//Bottom bar
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f ));
	mNamco = new Texture("NAMCO", "Minecraft.ttf", 36, { 200, 0, 0 });
	mDates = new Texture("1981 1982", "Minecraft.ttf", 36, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "Minecraft.ttf", 36, { 230 ,230, 230 });
	
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Pos(VEC2_ZERO);
	mDates->Pos(Vector2(0.0f, 90.0f));
	mRights->Pos(Vector2(0.0f, 170.0f));

	mBottomBar->Parent(this);

	mBottomRightText = new Texture("Tomas Minovsky", "Minecraft.ttf", 24, { 230, 230, 230 });
	mBottomRightText->Parent(mBottomBar);
	mBottomRightText->Pos(Vector2(390.0f, 250.0f));

	//Animation Vars
	ResetAnimation();

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen() {
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mHiScore;
	mHiScore = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	//scores
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mHiScoreBoard;
	mHiScoreBoard = NULL;
	
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;
	
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mPlayMode;
	mPlayMode = NULL;
	delete mOnePlayer;
	mOnePlayer = NULL;
	delete mTwoPlayer;
	mTwoPlayer = NULL;
	delete mCursor;
	mCursor = NULL;

	delete mBottomBar;
	mBottomBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mDates;
	mDates = NULL;
	delete mRights;
	mRights = NULL;
	
	delete mBottomRightText;
	mBottomRightText = NULL;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT * 1.5f);
	mAnimationEndPos = Vector2(0.0f, 0.0f);
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;

	mCursor->Pos(mCursorStartPos + (mCursorOffset * mSelectedMode));
}

void StartScreen::Update() {
	if (!mAnimationDone) {
		mAnimationTimer += Timer::Instance()->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			mStars->Scroll(false);
		}
		if(mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)
			|| mInput->KeyPressed(SDL_SCANCODE_W) || mInput->KeyPressed(SDL_SCANCODE_S)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else {
		mAnimatedLogo->Update();

		//if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
		//	ChangeSelectedMode(1);
		//else if (mInput->KeyPressed(SDL_SCANCODE_UP))
		//	ChangeSelectedMode(-1);
	}
}

void StartScreen::Render() {
	mTopBar->Render();
	mPlayerOne->Render();
	mHiScore->Render();
	//mPlayerTwo->Render();
	//scores
	mPlayerOneScore->Render();
	mHiScoreBoard->Render();
	//mPlayerTwoScore->Render();
	
	
	if (!mAnimationDone) {
		mLogo->Render();
	}
	else {
		mAnimatedLogo->Render();
	}
	
	//mPlayerTwo->Render();
	mPlayMode->Render();
	mOnePlayer->Render();
	//mTwoPlayer->Render();
	mCursor->Render();
	
	mBottomBar->Render();
	mNamco->Render();
	mDates->Render();
	mRights->Render();

	mBottomRightText->Render();
}