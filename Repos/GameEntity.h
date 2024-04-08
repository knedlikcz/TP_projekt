#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "MathHelper.h"

namespace QuickSDL {
	class GameEntity {

	public:
		enum SPACE { local = 0, world = 1 };

	private:
		Vector2 mPos;
		float mRotation;
		Vector2 mScale;

		bool mActive;

		GameEntity* mParent;

	public:

		GameEntity(Vector2 pos = VEC2_ZERO);
		~GameEntity();

		void Pos(Vector2 pos);

		Vector2 Pos(SPACE space = world);

		void Rotation(float rotation);

		float Rotation(SPACE space = world);

		void Scale(Vector2 scale);

		Vector2 Scale(SPACE space = world);

		void Active(bool active);

		bool Active();

		void Parent(GameEntity* parent);

		GameEntity* Parent();

		void Translate(Vector2 vec, SPACE space = local);

		void Rotate(float amount);

		virtual void Update();
		virtual void Render();
	};
}
#endif
