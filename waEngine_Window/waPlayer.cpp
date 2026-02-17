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

	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}