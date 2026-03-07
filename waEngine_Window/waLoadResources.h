#pragma once
#pragma once
#include "..\\waEngine_SOURCE\\waResources.h"
#include "..\\waEngine_SOURCE\\waTexture.h"


namespace wa
{
	void LoadResources()
	{
		// Title
		Resources::Load<graphics::Texture>(L"TitleLogo", L"..\\Resources\\UI\\TitleLogo.bmp");
		Resources::Load<graphics::Texture>(L"TitleLogo_Bot", L"..\\Resources\\UI\\TitleLogo_Bot.bmp");
		Resources::Load<graphics::Texture>(L"Title_Stage", L"..\\Resources\\Actor\\Stage\\Title_Stage.bmp");
		Resources::Load<graphics::Texture>(L"Title_Back", L"..\\Resources\\Level\\Title_Back.bmp");

		// Level_1
		Resources::Load<graphics::Texture>(L"Level1", L"..\\Resources\\Actor\\Stage\\Level1.bmp");


		// Kirby
		Resources::Load<graphics::Texture>(L"Kirby_Left", L"..\\Resources\\Actor\\Kirby\\Default_Left.bmp");
		Resources::Load<graphics::Texture>(L"Kirby_Right", L"..\\Resources\\Actor\\Kirby\\Default_Right.bmp");
		
		// Enemies
		Resources::Load<graphics::Texture>(L"BigWaddleDee_Left", L"..\\Resources\\Actor\\Monster\\BigWaddleDee_Left.bmp");
		Resources::Load<graphics::Texture>(L"BigWaddleDee_Right", L"..\\Resources\\Actor\\Monster\\BigWaddleDee_Right.bmp");
	}
}