#include"Class.h"
INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrew,LPSTR lpsz,INT nShow)
{
	srand((INT)time(NULL));
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wnd;
	wnd.cbSize=sizeof(wnd);
	wnd.style=NULL;CS_HREDRAW|CS_VREDRAW;
	wnd.lpfnWndProc=CDlgUserClass::WndProc;
	wnd.cbClsExtra=0;
	wnd.cbWndExtra=0;
	wnd.hInstance=hInst;
	wnd.hIcon=LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));
	wnd.hCursor=LoadCursor(NULL,IDC_ARROW);
	wnd.lpszMenuName=NULL;
	wnd.hIconSm=LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));
	wnd.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszClassName=L"Мой оконный класс";
	if(!RegisterClassEx(&wnd))
	{
		MessageBox(NULL,L"Ошибка регистрации окна",L"Error",MB_OK);
		return 1;
	}
	hwnd=CreateWindowEx(WS_EX_TOPMOST,wnd.lpszClassName,L"Tanki",WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,0,0,425,445,NULL,NULL,hInst,NULL);
	ShowWindow(hwnd,nShow);
	UpdateWindow(hwnd);

	CLevel lvl(hwnd);
	if(lvl.Menu())
	{
		SetTimer(hwnd,100500,1,lvl.TimerProc);
	}
	else
		return 0;
	while(GetMessage(&msg,NULL ,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}