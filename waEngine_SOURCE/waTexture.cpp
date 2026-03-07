#include "waTexture.h"
#include "waApplication.h"

// 해당 전역변수가 존재함을 알리는 키워드
extern wa::Application application;

namespace wa::graphics
{
	Texture::Texture()
		: Resource(enums::eResourceType::Texture)
	{

	}
	Texture::~Texture()
	{
	}
	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);
		
		// bmp 일때
		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP
				, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);

		}
		else if (ext == L"png")
		{
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());
			if (mImage == nullptr)
				return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}

	COLORREF Texture::GetPixel(int x, int y)
	{
		// 1. 비트맵 범위 밖 예외 처리
		if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
			return RGB(255, 255, 255); // 범위 밖은 공중 처리

		// 2. GDI GetPixel은 느리므로, 맵 로드 시점에 
		// 메모리 DC(mHdc)를 생성해두고 거기서 가져오는 것이 좋습니다.
		return ::GetPixel(mHdc, x, y);
	}

}