// HelloWorldBHO.h : Declaration of the CHelloWorldBHO

#pragma once
#include "resource.h"       // main symbols
#include <shlguid.h>     // IID_IWebBrowser2, DIID_DWebBrowserEvents2, etc.
#include "HelloWorld.h"
#include <mshtml.h>
#include <exdispid.h> // DISPID_DOCUMENTCOMPLETE, etc.

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CHelloWorldBHO

class ATL_NO_VTABLE CHelloWorldBHO :
	public IDispEventImpl<1, CHelloWorldBHO, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHelloWorldBHO, &CLSID_HelloWorldBHO>,
	public IObjectWithSiteImpl<CHelloWorldBHO>,
	public IDispatchImpl<IHelloWorldBHO, &IID_IHelloWorldBHO, &LIBID_HelloWorldLib, /*wMajor =*/ 1, /*wMinor =*/ 0>

{

private:
    CComPtr<IWebBrowser2>  m_spWebBrowser;
	BOOL m_fAdvised; 
	int DocumentCompleteCount=0;
	int BeforeNavigate2Count=0;
	int NavigateComplete2Count=0;
	int DownloadCompleteCount=0;
	int OnQuitCount =0;
	int WindowStateChangedCount =0;


public:
	//Sink the events into our local methods
	STDMETHOD(SetSite)(IUnknown *pUnkSite);
	//https://msdn.microsoft.com/en-us/library/kdbd8xsk.aspx
	BEGIN_SINK_MAP(CHelloWorldBHO)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE,    OnDocumentComplete)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2,     OnBeforeNavigate2)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOWNLOADCOMPLETE,    OnDownloadComplete)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2,   OnNavigateComplete2)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_ONQUIT,              OnQuit)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_WINDOWSTATECHANGED, OnWindowStateChanged)
	END_SINK_MAP()
	void STDMETHODCALLTYPE OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);
	void STDMETHODCALLTYPE OnWindowStateChanged(IDispatch *pDisp, VARIANT *pvarURL); 
	void STDMETHODCALLTYPE OnBeforeNavigate2(IDispatch *pDisp, VARIANT *pvarURL); 
	void STDMETHODCALLTYPE OnDownloadComplete(IDispatch *pDisp, VARIANT *pvarURL); 
	void STDMETHODCALLTYPE OnNavigateComplete2(IDispatch *pDisp, VARIANT *pvarURL); 
	void STDMETHODCALLTYPE OnQuit(IDispatch *pDisp, VARIANT *pvarURL); 
	HWND WindowHandle;



	CHelloWorldBHO()
	{
		//configure our class and register it
		WNDCLASSEXW wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hDLL;
		wcex.hIcon = LoadIcon(hDLL, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
		wcex.lpszClassName = L"DISPLAY";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		RegisterClassExW(&wcex);

		//create the window and store the handle
		WindowHandle = CreateWindowW(wcex.lpszClassName, L"EventDisplay", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hDLL, nullptr);

		ShowWindow(WindowHandle, NULL);
		UpdateWindow(WindowHandle);
		


	}

	///Message handling for the class
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{

				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_HELLOWORLDBHO)

DECLARE_NOT_AGGREGATABLE(CHelloWorldBHO)

BEGIN_COM_MAP(CHelloWorldBHO)
	COM_INTERFACE_ENTRY(IHelloWorldBHO)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

};

OBJECT_ENTRY_AUTO(__uuidof(HelloWorldBHO), CHelloWorldBHO)
