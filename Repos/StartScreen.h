#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"

#include "BackgroundStars.h"
#include "ScoreBoard.h"

#include "tinyxml2.h"

using namespace tinyxml2;
	class StartScreen : public GameEntity {
	public:
		StartScreen();
		~StartScreen();

		void ResetAnimation();

		int SelectedMode();
		
		void ChangeSelectedMode(int change);

		void Update();

		void Render();
	private:

		Timer* mTimer;
		InputManager* mInput;
		
		//Top bar
		GameEntity* mTopBar;
		Texture* mPlayerOne;
		Texture* mHiScore;
		Texture* mPlayerTwo;
		ScoreBoard* mPlayerOneScore;
		ScoreBoard* mHiScoreBoard;
		ScoreBoard* mPlayerTwoScore;

		//Logo
		Texture* mLogo;
		AnimatedTexture* mAnimatedLogo;

		//Play mode 
		GameEntity* mPlayMode;
		Texture* mOnePlayer;
		Texture* mTwoPlayer;
		Texture* mCursor;
		Vector2 mCursorStartPos;
		Vector2 mCursorOffset;
		int mSelectedMode;
		
		//Bottom bar
		GameEntity* mBottomBar;
		Texture* mNamco;
		Texture* mDates;
		Texture* mRights;

		//Animation Vars
		Vector2 mAnimationStartPos;
		Vector2 mAnimationEndPos;
		float mAnimationTotalTime;
		float mAnimationTimer;
		bool mAnimationDone;

		//BottomRightText
		Texture* mBottomRightText;

		BackgroundStars* mStars;

		XMLDocument Scores;
		int HScore;
	};

#endif
