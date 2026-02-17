#pragma once
#pragma once
#include "..\\waEngine_SOURCE\\waResources.h"
#include "..\\waEngine_SOURCE\\waTexture.h"


namespace wa
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"Map", L"C:\\wa\\waEngine\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PacMan", L"C:\\wa\\waEngine\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>(L"Link", L"C:\\wa\\waEngine\\Resources\\Link.png");
		Resources::Load<graphics::Texture>(L"MapleEffect", L"C:\\wa\\waEngine\\Resources\\effect.png");
	}
}