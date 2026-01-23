#include "waGameObject2.h"

ya::GameObject2::GameObject2()
{

}

ya::GameObject2::~GameObject2()
{
}

void ya::GameObject2::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mY -= 0.01f;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mY += 0.01f;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mX -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mX += 0.01f;
	}

}

void ya::GameObject2::LateUpdate()
{

}

void ya::GameObject2::Render(HDC hdc)
{

	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, greenBrush);
	
	Ellipse(hdc, 500 + mX, 500 + mY, 600 + mX, 600 + mY);

	DeleteObject(greenBrush);
	SelectObject(hdc, oldBrush);

}