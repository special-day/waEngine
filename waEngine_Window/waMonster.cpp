#include "waMonster.h"
#include "waPlayer.h"
#include "waInput.h"
#include "waTransform.h"
#include "waTime.h"

namespace wa
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}