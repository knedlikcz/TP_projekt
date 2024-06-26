#ifndef _ENEMY_H
#define _ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"
#include "PhysEntity.h"
#include "Player.h"

class Enemy : public PhysEntity {

public:
	enum STATES { flyIn, formation, dive, dead };
	enum TYPES { butterfly, wasp, boss };

protected:
	
	static std::vector<std::vector<Vector2>> sPaths;
	static Formation* sFormation;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTextures[2];

	STATES mCurrentState;

	int mCurrentPath;

	int mCurrentWaypoint;
	const float EPSILON = 50.0f;
	
	float mSpeed;

	TYPES mType;
	int mIndex;

	bool mChallangeStage;

	Vector2 mDiveStartPosition;

	AnimatedTexture* mDeathAnimation;

protected:

	virtual void PathComplete();

	virtual void FlyInComplete();

	void JoinFormation();
	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;
	
	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState();

	void RenderStates();

	bool IgnoreCollisions() override;

public:

	static void CreatePaths();
	static void SetFormation(Formation* f);
	static void CurrentPlayer(Player* p);

	Enemy(int index, int path, bool challengeStage);
	virtual ~Enemy();

	virtual void Hit(PhysEntity* other) override;

	STATES CurrentState();
	TYPES Type();
	int Index();

	virtual void Dive(int type = 0);

	bool InDeathAnimation();
	
	void Update();
	void Render();

};

#endif 
