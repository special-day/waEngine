#pragma once
#include "waGameObject.h"
#include "waGameObject2.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd, UINT width, UINT height);
		void Run();

		void Update();
		void LateUpdate();

		void Render();

	private:
		HWND mHwnd;
		HDC  mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject  mPlayer;
		GameObject2 mObj;
	};
}

