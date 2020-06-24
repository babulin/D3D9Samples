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
 *| ��������
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
	OutputDebugString(L"GameWind()����\n");
	//1������
	WNDCLASS wc;
	wc.cbClsExtra = 0;										//�������ڴ棬ͨ��Ϊ��
	wc.cbWndExtra = 0;										//���ڶ�����ڴ棬ͨ��Ϊ��
	wc.hbrBackground = NULL;// (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ñ���
	wc.hCursor = LoadCursor(NULL, IDC_HAND);				//���ù�꣬�����һ������ΪNULL������ʹ��ϵͳ�ṩ��Ĭ�Ϲ��
	wc.hIcon = LoadIcon(NULL, IDC_ICON);					//LOGO
	wc.hInstance = mhInstance;								//��ǰʵ�������WinMain�������βμ���
	wc.lpfnWndProc = GameWind::WindowProc;							//���ڹ��̺������ص����������ƿ��������
	wc.lpszClassName = mWndClassName;							//ָ����������
	wc.lpszMenuName = NULL;									//�˵�����û����NULL
	wc.style = 0;											//0����Ĭ�Ϸ��

	//2��ע�ᴰ��
	RegisterClass(&wc);

	//3������ͻ�����С
	int screenW = GetSystemMetrics(SM_CXSCREEN);//��ȡ��Ļ��С
	int screenH = GetSystemMetrics(SM_CYSCREEN);//��ȡ��Ļ��С

	int mX = (screenW / 2) - (WIDTH / 2);
	int mY = (screenH / 2) - (HEIGHT / 2);

	wcRect = { 0,0,0,0 };
	SetRect(&wcRect, mX, mY, static_cast<int>(mWidth) + mX, static_cast<int>(mHeight) + mY);
	AdjustWindowRect(&wcRect, WS_OVERLAPPEDWINDOW, false);

	//4����������
	mHwnd = CreateWindow(
		wc.lpszClassName,				//����
		mWndClassName,						//������
		WS_OVERLAPPEDWINDOW,			//��ʾ���  WS_OVERLAPPEDWINDOW
		wcRect.left,					//��ʼ���� x CW_USEDEFAULT
		wcRect.top,						//��ʼ���� y CW_USEDEFAULT
		wcRect.right - wcRect.left,		//���ڿ�� nWidth
		wcRect.bottom - wcRect.top,		//���ڸ߶� nHeight
		NULL,							//�����ڣ�NULL
		NULL,							//�˵�  NULL
		mhInstance,						//ʵ�������hInstance
		NULL							//��������   NULL
	);

	if (mHwnd == NULL)
	{
		MessageBox(NULL, TEXT("��������ʧ��"), TEXT("������ʾ"), MB_OK);
	}

	GetClientRect(mHwnd, &clientRect);

	//5����ʾ�͸���
	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	UpdateWindow(mHwnd);
}

GameWind::GameWind(const GameWind& wnd)
{
	OutputDebugString(L"GameWind()��������\n");
	mHwnd = wnd.mHwnd;
	mhInstance = wnd.mhInstance;
	mWidth = wnd.mWidth;
	mHeight = wnd.mHeight;
	wcRect = wnd.wcRect;
}

GameWind::~GameWind()
{
	OutputDebugString(L"~GameWind()����\n");
	UnregisterClass(mWndClassName, mhInstance);
}

void GameWind::ShowWind()
{
	isShow = IsWindowVisible(mHwnd);
	if (!isShow)
	{
		//5����ʾ�͸���
		ShowWindow(mHwnd, SW_SHOWDEFAULT);
		UpdateWindow(mHwnd);
	}
}
/**
 * ����ϵͳ��Ϣ
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

//������Ϣ����ص�
LRESULT CALLBACK GameWind::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	TCHAR buf[1024];
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);                //����WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);                  //�����˳���Ϣ
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
	case WM_LBUTTONDOWN:                      //������������Ϣ
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"�������:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, L_BUTTON_DOWN);
		break;
	}
	case WM_LBUTTONUP:                      //������������Ϣ
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"�������:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, L_BUTTON_UP);

		break;
	}
	case WM_RBUTTONDOWN:                      //����Ҽ�������Ϣ
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"�Ҽ�����:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, R_BUTTON_DOWN);
		break;
	}
	case WM_RBUTTONUP:                      //����Ҽ�������Ϣ
	{
		gWnd->mMouse.x = LOWORD(lParam);
		gWnd->mMouse.y = HIWORD(lParam);
		wsprintf(buf, L"�Ҽ�����:%d,%d\n", gWnd->mMouse.x, gWnd->mMouse.y);
		OutputDebugString(buf);
		if (gWnd->keyMouse != nullptr)
			gWnd->keyMouse(gWnd->mMouse.x, gWnd->mMouse.y, R_BUTTON_UP);
		break;
	}
	case WM_KEYDOWN:       //������Ϣ
	{
		wsprintf(buf, L"���̰���:%c\n", wParam);
		OutputDebugString(buf);
		//if (gWnd->KeyBoard != nullptr)
			//gWnd->KeyBoard(wParam, KB_DOWN);
		break;
	}
	case WM_KEYUP:       //������Ϣ
	{
		wsprintf(buf, L"���̰���:%c\n", wParam);
		OutputDebugString(buf);
		//if (gWnd->KeyBoard != nullptr)
			//gWnd->KeyBoard(wParam, KB_UP);
		break;
	}
	case WM_MOUSEMOVE:
	{
		//gWnd->mMouse.x = LOWORD(lParam); //ȡ��x������
		//gWnd->mMouse.y = HIWORD(lParam); //ȡ��y������
		break;
	}
	default:
		break;
	}
	//Ĭ�Ϸ�ʽ����
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

