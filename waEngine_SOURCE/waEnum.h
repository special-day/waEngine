#pragma once

namespace wa::enums
{
	enum class eComponentType
	{
		Transform,
		Collider,
		Script,
		Animator,
		SpriteRenderer,
		Camera,
		End,
	};

	enum class eLayerType
	{
		None,
		BackGround,
		UI,
		Player,
		Monster,
		Particle,
		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation, 
		Prefab,
		End,
	};

	enum class eColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};
}