#pragma once

#include "waEntity.h"
#include "waComponent.h"

namespace wa
{
	using namespace math;
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void SetPos(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPos() { return mPosition; }

	private:
		Vector2 mPosition;

	};
}

