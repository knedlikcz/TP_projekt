#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H
#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity{
private:
	Timer* mTimer;
	AudioManager* mAudio;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	ScoreBoard* mHighScoreBoard;

	Texture* mPlayerOneLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mPlayerOneLabelVisible;
	ScoreBoard* mPlayerOneScore;

	static const int MAX_SHIP_TEXTURES = 5;
	GameEntity* mShips;
	Texture* mShipTextures[MAX_SHIP_TEXTURES];
	ScoreBoard* mTotalShipsLabel;
	int mTotalShips;

	GameEntity* mFlags;
	std::vector<Texture*> mFlagTextures;
	int mRemainingLevels;
	int mFlagXOffset;
	int mFlagTimer;
	int mFlagInterval;

private:
	
	void ClearFlags();
	void AddNextFlag();
	void AddFlag(std::string filename, int width, int value);
	
public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerOneScore(int score);
	void SetShips(int ship);
	void SetLevel(int level);

	int GetHighScore();

	void Update();
	void Render();
};

#endif // !_PLAYSIDEBAR_H
