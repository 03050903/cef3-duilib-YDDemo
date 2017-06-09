//
// main.cpp
#include "simple_app.h"
#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>

#include "..\DuiLib\Utils\WinImplBase.h"
#include "MainFrame.h"

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{

	CPaintManagerUI::SetInstance(hInstance);

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if( FAILED(Hr) ) return 0;

	CefMainArgs args(hInstance);

	//����CefAppʵ��
	CefRefPtr<SimpleApp> app(new SimpleApp);

	// ���������ִ����browser����ʱ���������أ�
	// ���ӽ���ʱ�����ֱ���˳�ʱ���ء�
	int exitCode = CefExecuteProcess(args, app, NULL);
	if (exitCode >= 0)
	{
		return exitCode;
	}

	//�������ṹ�壬���ڶ���CEF����Ϊ��
	CefSettings settings;

	//��ʼ��CEF
	CefInitialize(args, settings, app, NULL);


	CMainFrame* pFrame = new CMainFrame();
	if( pFrame == NULL ) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
	pFrame->Create(NULL, _T("PLApp"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
#else
	pFrame->Create(NULL, _T("PLApp"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
	HICON hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	::SendMessage(*pFrame, STM_SETICON, IMAGE_ICON, (LPARAM)(UINT)hIcon);

	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);
	//ִ����Ϣѭ��,��ʱ�������ֱ��CefQuitMessageLoop()���������á�
	CefRunMessageLoop();


	// �ر�CEF���ͷ���Դ  
	CefShutdown();
	/*CPaintManagerUI::MessageLoop();*/

	return 0;
}