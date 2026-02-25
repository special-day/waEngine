#include "waBackground.h"

namespace wa
{
	Background::Background()
	{
	}
	Background::~Background()
	{
	}
	void Background::Initialize()
	{
		GameObject::Initialize();
	}

	void Background::Update()
	{
		GameObject::Update();
	}
	
	void Background::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	
	void Background::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
}