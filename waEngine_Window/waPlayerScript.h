#pragma once
#include "..\\waEngine_SOURCE\\\waScript.h"

namespace wa
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
		};


		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		void idle();
		void move();

	private:
		eState mState;
		class Animator* mAnimator;
	};
}