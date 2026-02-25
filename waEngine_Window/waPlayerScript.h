#pragma once
#include "..\\waEngine_SOURCE\\\waScript.h"

namespace wa
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Stand,
			Walk,
			Run,
			Crouch,
			Slide,
		};


		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void AttackEffect();

	private:
		void stand();
		void walk();
		void run();


	private:
		eState mState;
		class Animator* mAnimator;

		//void (*StartEvent)();
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}