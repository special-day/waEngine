#include "waTransform.h"
#include "waInput.h"
#include "waTime.h"

namespace wa
{
	Transform::Transform()
		: mX(0)
		, mY(0)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
		const float speed = 100.0f;
        if (Input::GetKey(eKeyCode::A))
        {
            mX -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::D))
        {
            mX += speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::W))
        {
            mY -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::S))
        {
            mY += speed * Time::DT();
        }
	}
	void Transform::LateUpdate()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
}