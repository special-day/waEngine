#include "waComponent.h"

namespace wa
	{
	Component::Component()
		: mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}

	void Component::Initialize()
	{

	}
	void Component::Update()
	{
	}
	void Component::LateUpdate()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}