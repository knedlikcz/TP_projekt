#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mShip = new Texture("PlayerShip.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);
	
	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(40.0f, 740.0f);

	mDeathAnimation = new AnimatedTexture("playerexp.png", 0, 0, 125, 128, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}

	AddCollider(new BoxCollider(Vector2(15.0f, 67.0f)));
	AddCollider(new BoxCollider(Vector2(15.0f, 40.0f)), Vector2(15.0f, 10.0f));
	AddCollider(new BoxCollider(Vector2(15.0f, 40.0f)), Vector2(-15.0f, 10.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player() {

	mTimer = NULL;
	mInput = NULL;

	delete mShip;
	mShip = NULL;
	
	delete mDeathAnimation;
	mDeathAnimation = NULL;
	
	for (int i = 0; i < MAX_BULLETS; i++) {
		delete mBullets[i];
		mBullets[i] = NULL;
	}
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_A))
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
	else if (mInput->KeyDown(SDL_SCANCODE_D))
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	Pos(pos);
}

void Player::HandleFieing() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Pos());
				break;
			}
		}
	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

void Player::Hit(PhysEntity* other) {
	mLives--;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

void Player::Update() {
	if (mAnimating) {

		if(mWasHit)
			mWasHit = false;
		
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFieing();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Render();
	}

	PhysEntity::Render();
}