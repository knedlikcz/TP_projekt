#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h" 
#include "InputManager.h"
#include "Bullet.h"

using namespace QuickSDL;

class Player : public PhysEntity {

private:
	
	Timer* mTimer;
	InputManager* mInput;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	int mScore;
	int mLives;

	Texture* mShip;

	AnimatedTexture* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

private:

	bool IgnoreCollisions() override;

	void HandleMovement();
	void HandleFieing();

public:
	Player();
	~Player();

	void Visible(bool visible);
	void Hit(PhysEntity* other) override;
	bool WasHit();
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void Update();
	void Render();
};

#endif