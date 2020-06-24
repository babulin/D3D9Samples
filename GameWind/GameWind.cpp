#include "GameWind.h"
GameWind* gWnd;

GameWind* windCreate(HINSTANCE hInstance, int width, int hegiht, const wchar_t* wndClassName) {
	if (!gWnd)
	{
		gWnd = new GameWind(hInstance, width, hegiht, wndClassName);
		return gWnd;
	}
	return gWnd;
}

/*+---------------------------------------------------
 *| 创建窗口
 *+---------------------------------------------------
 */
GameWind::GameWind(HINSTANCE hInstacne, int width, int height, const wchar_t* wndClassName)
	:
	mhInstance(hInstacne),
	mWidth(width),
	mHeight(height),
	isShow(false),
	mWndClassName(wndClassName),
	wcRect({ 0 }),
	clientRect({ 0 })
{
	OutputDebugString(L"GameWind()构造\n");
	//1、对象
	WNDCLASS wc;
	wc.cbClsExtra = 0;										//类额外的内存，通常为零
	wc.cbWndExtra = 0;										//窗口额外的内存，通常为零
	wc.hbrBackground = NULL;// (HBRUSH)GetStockObject(BLACK_BRUSH);	//设置背景
	wc.hCursor = LoadCursor(NULL, IDC_HAND);				//设置光标，如果第一个参数为NULL，代表使用系统提供的默认光标
	wc.hIcon = LoadIcon(NULL, IDC_ICON);					//LOGO
	wc.hInstance = mhInstance;								//当前实例句柄，WinMain函数中形参即可
	wc.lpfnWndProc = GameWind::WindowProc;							//窗口过程函数，回调函数，名称可以随便起
	wc.lpszClassName = mWndClassName;							//指定窗口类名
	wc.lpszMenuName = NULL;									//菜单名，没有填NULL
	wc.style = 0;											//0代表默认风格

	//2、注册窗口
	RegisterClass(&wc);

	//3、计算客户区大小
	int screenW = GetSystemMetrics(SM_CXSCREEN);//获取屏幕大小
	int screenH = GetSystemMetrics(SM_CYSCREEN);//获取屏幕大小

	int mX = (screenW / 2) - (WIDTH / 2);
	int mY = (screenH / 2) - (HEIGHT / 2);

	wcRect = { 0,0,0,0 };
	SetRect(&wcRect, mX, mY, static_cast<int>(mWidth) + mX, static_cast<int>(mHeight) + mY);
	AdjustWindowRect(&wcRect, WS_OVERLAPPEDWINDOW, false);

	//4、创建窗口
	mHwnd = CreateWindow(
		wc.lpszClassName,				//类名
		mWndClassName,						//窗口名
		WS_OVERLAPPEDWINDOW,			//显示风格  WS_OVERLAPPEDWINDOW
		wcRect.left,					//起始坐标 x CW_USEDEFAULT
		wcRect.top,						//起始坐标 y CW_USEDEFAULT
		wcRect.right - wcRect.left,		//窗口宽度 nWidth
		wcRect.bottom - wcRect.top,		//窗口高度 nHeight
		NULL,							//父窗口，NULL
		NULL,							//菜单  NULL
		mhInstance,						//实例句柄，hInstance
		NULL							//其他参数   NULL
	);

	if (mHwnd == NULL)
	{
		MessageBox(NULL, TEXT("创建窗口失败"), TEXT("错误提示"), MB_OK);
	}

	GetClientRect(mHwnd, &clientRect);

	//5、显示和更新
	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	UpdateWindow(mHwnd);
}

GameWind::GameWind(const GameWind& wnd)
{
	OutputDebugString(L"GameWind()拷贝构造\n");
	mHwnd = wnd.mHwnd;
	mhInstance = wnd.mhInstance;
	mWidth = wnd.mWidth;
	mHeight = wnd.mHeight;
	wcRect = wnd.wcRect;
}

GameWind::~GameWind()
{
	OutputDebugString(L"~GameWind()析构\n");
	UnregisterClass(mWndClassName, mhInstance);
}

void GameWind::ShowWind()
{
	isShow = IsWindowVisible(mHwnd);
	if (!isShow)
	{
		//5、显示和更新
		ShowWindow(mHwnd, SW_SHOWDEFAULT);
		UpdateWindow(mHwnd);
	}
}
/**
 * 处理系统消息
 */
bool GameWind::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

void GameWind::ShowMessageBox(const wchar_t* title, const wchar_t* msg)
{
	MessageBox(mHwnd, msg, title, MB_OK);
}

//窗口消息处理回调
LRESULT CALLBACK GameWind::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	TCHAR buf[1024];
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);                //触发WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);                  //发送退出消息
		break;
	case WM_SIZE:
	{
		if (gWnd)
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			gWnd->mWidth = width;
			gWnd->mHeight = height;
		}
		break;
	}
	case WM_LBUTTONDOWN:                      //鼠标左键按下消息
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"左键按下:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, L_BUTTON_DOWN);
		break;
	}
	case WM_LBUTTONUP:                      //鼠标左键弹起消息
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"左键弹起:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, L_BUTTON_UP);

		break;
	}
	case WM_RBUTTONDOWN:                      //鼠标右键按下消息
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"右键按下:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, R_BUTTON_DOWN);
		break;
	}
	case WM_RBUTTONUP:                      //鼠标右键弹起消息
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"右键弹起:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, R_BUTTON_UP);
		break;
	}
	case WM_KEYDOWN:       //键盘消息
	{
		wsprintf(buf, L"键盘按下:%c\n", wParam);
		OutputDebugString(buf);
		//if (gWnd->KeyBoard != nullptr)
			//gWnd->KeyBoard(wParam, KB_DOWN);
		break;
	}
	case WM_KEYUP:       //键盘消息
	{
		wsprintf(buf, L"键盘按下:%c\n", wParam);
		OutputDebugString(buf);
		//if (gWnd->KeyBoard != nullptr)
			//gWnd->KeyBoard(wParam, KB_UP);
		break;
	}
	case WM_MOUSEMOVE:
	{
		//gWnd->mMouse.x = LOWORD(lParam); //取得x的坐标
		//gWnd->mMouse.y = HIWORD(lParam); //取得y的坐标
		break;
	}
	default:
		break;
	}
	//默认方式处理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

