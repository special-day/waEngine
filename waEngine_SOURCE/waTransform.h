#pragma once
#include "waComponent.h"

namespace wa
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void SetPos(float x, float y) { mX = x; mY = y; }
		float GetX() { return mX; }
		float GetY() { return mY; }

	private:
		float mX;
		float mY;

	};
}

