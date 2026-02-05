#pragma once
#pragma once
#include "..\\waEngine_SOURCE\\waResources.h"
#include "..\\waEngine_SOURCE\\waTexture.h"


namespace wa
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"BG", L"C:\\wa\\waEngine\\Resources\\simple.png");
	}
}