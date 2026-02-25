#pragma once
#pragma once
#include "..\\waEngine_SOURCE\\waResources.h"
#include "..\\waEngine_SOURCE\\waTexture.h"


namespace wa
{
	void LoadResources()
	{
		// Title
		Resources::Load<graphics::Texture>(L"TitleLogo", L"C:\\wa\\waEngine\\Resources\\UI\\TitleLogo.bmp");
		Resources::Load<graphics::Texture>(L"TitleLogo_Bot", L"C:\\wa\\waEngine\\Resources\\UI\\TitleLogo_Bot.bmp");
		Resources::Load<graphics::Texture>(L"Title_Stage", L"C:\\wa\\waEngine\\Resources\\Actor\\Stage\\Title_Stage.bmp");
		Resources::Load<graphics::Texture>(L"Title_Back", L"C:\\wa\\waEngine\\Resources\\Level\\Title_Back.bmp");

		Resources::Load<graphics::Texture>(L"Kirby_Left", L"C:\\wa\\waEngine\\Resources\\Actor\\Kirby\\Default_Left.bmp");
		Resources::Load<graphics::Texture>(L"Kirby_Right", L"C:\\wa\\waEngine\\Resources\\Actor\\Kirby\\Default_Right.bmp");
		// Resources::Load<graphics::Texture>(L"Enemies", L"C:\\wa\\waEngine\\Resources\\Enemies.bmp");
	}
}