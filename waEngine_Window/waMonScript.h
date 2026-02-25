#pragma once
#include "..\\waEngine_SOURCE\\waScript.h"
#include "..\\waEngine_SOURCE\\waTransform.h"

namespace wa
{
	class MonScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
		};

		enum class eDirection
		{
			Left,
			Right,
			End,
		};


		MonScript();
		~MonScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		void idle();
		void move();
		void playWalkAnimationByDirection(eDirection dir);
		void translate(Transform* tr);

	private:
		eState mState;
		class Animator* mAnimator;
		eDirection mDirection;
		float mTime;
		float mDeathTime;
	};
}