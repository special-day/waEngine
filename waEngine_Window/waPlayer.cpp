#include "waPlayer.h"
#include "waInput.h"
#include "waTransform.h"
#include "waTime.h"

namespace wa
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if (Input::GetKey(eKeyCode::Right))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 100.0f * Time::DT();
			tr->SetPos(pos);
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}