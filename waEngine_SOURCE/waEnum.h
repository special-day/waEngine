#pragma once


namespace wa::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Player,
		Monster,
		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End,
	};
}