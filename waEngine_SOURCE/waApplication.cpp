#include "waApplication.h"
#include "waInput.h"
#include "waTime.h"
#include "waSceneManager.h"
#include "waResources.h"

namespace wa
{

    Application::Application()
        : mHwnd(nullptr)
        , mHdc(nullptr)
        , mWidth(0)
        , mHeight(0)
        , mBackHdc(NULL)
        , mBackBitmap(NULL)
    {
    }

    Application::~Application()
    {
    }

    void Application::Initialize(HWND hwnd, UINT width, UINT height)
    {
        adjustWindowRect(hwnd, width, height);
        createBuffer(mWidth, mHeight);
        initializeEtc();

		SceneManager::Initialize();
    }

    void Application::Run()
    {
        Update();
        LateUpdate();
        Render();
        Destroy();
    }

    void Application::Update()
    {
        Input::Update();
        Time::Update();
		SceneManager::Update();
    }

    void Application::LateUpdate()
    {
		SceneManager::LateUpdate();
    }

    void Application::Render()
    {
        clearRenderTarget();

        Time::Render(mBackHdc);

		SceneManager::Render(mBackHdc);

        copyRenderTarget(mBackHdc, mHdc);

        // mObj.Render(mHdc);

        // 기본으로 자주 사용되는 GDI 오브젝트를 미리 DC 안에 만들어 두었는데
        // 그 오브젝트들을 스톡 오브젝트라고 한다.

        // DC란 화면에 출력에 필요한 모든 정보를 가지는 데이터 구조체이며
        // GDI 모듈에 의해서 관리된다.
        // 어떤 폰트를 사용할 것인가? 어떤 선의 굵기를 정해줄 것인지? 어떤 색상으로 그려줄 것인지?
        // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.
    }

    void Application::Destroy()
    {
        SceneManager::Destroy();
    }

    void Application::Release()
    {
        SceneManager::Release();
        Resources::Release();
    }

    void Application::clearRenderTarget()
    {
        Rectangle(mBackHdc, -1, -1, 1601, 901);
    }
    void Application::copyRenderTarget(HDC source, HDC dest)
    {
        BitBlt(mHdc, 0, 0, mWidth, mHeight
            , mBackHdc, 0, 0, SRCCOPY);
    }
    void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
    {
        mHwnd = hwnd;
        mHdc = GetDC(hwnd);

        RECT rect = { 0, 0, width, height };
        AdjustWindowRect(&rect, WS_OVERLAPPED, false);

        mWidth = rect.right - rect.left;
        mHeight = rect.bottom - rect.top;

        SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
    }
    void Application::createBuffer(UINT width, UINT height)
    {
        mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
        mBackHdc = CreateCompatibleDC(mHdc);

        HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
        DeleteObject(oldBitmap);
    }
    void Application::initializeEtc()
    {
        Input::Initialize();
        Time::Initialize();
    }

}