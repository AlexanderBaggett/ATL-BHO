// HelloWorldBHO.cpp : Implementation of CHelloWorldBHO

#include "stdafx.h"
#include "HelloWorldBHO.h"
#include <comdef.h>
#include <string>
#include "HelloWorld.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


using namespace std;

// CHelloWorldBHO

STDMETHODIMP CHelloWorldBHO::SetSite(IUnknown* pUnkSite)
{
    if (pUnkSite != NULL)
    {
        // Cache the pointer to IWebBrowser2.
        HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void **)&m_spWebBrowser);
        if (SUCCEEDED(hr))
        {
            // Register to sink events from DWebBrowserEvents2.
            hr = DispEventAdvise(m_spWebBrowser);
            if (SUCCEEDED(hr))
            {
                m_fAdvised = TRUE;
            }
        }
    }
    else
    {
        // Unregister event sink.
        if (m_fAdvised)
        {
            DispEventUnadvise(m_spWebBrowser);
            m_fAdvised = FALSE;
        }

        // Release cached pointers and other resources here.
        m_spWebBrowser.Release();
    }

    // Call base class implementation.
    return IObjectWithSiteImpl<CHelloWorldBHO>::SetSite(pUnkSite);
}

bool CheckIFBOA(VARIANT * pvarURL, HWND hwnd)
{

		_variant_t vt(pvarURL);
		_bstr_t bstr(vt);
		string URL = (char*) bstr;
		int pos = URL.find("bankofamerica.com");
		if(pos != -1)


		{
			MessageBox(hwnd, L"Bank of America", L"BHO", MB_OK);
			return true;
		}
		else
		{
			MessageBox(hwnd, L"This is not Bank of America", L"BHO", MB_OK);
			return false;
		}
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
		//do stuff with WindowHandle here to update the text on it.
		CheckIFBOA(pvarURL,hwnd);

    }
	DocumentCompleteCount++;
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnWindowStateChanged (IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
		CheckIFBOA(pvarURL,hwnd);

    }
	WindowStateChangedCount++;
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnDownloadComplete (IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
			CheckIFBOA(pvarURL,hwnd);
		
    }
	DownloadCompleteCount++;
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnQuit (IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
			CheckIFBOA(pvarURL,hwnd);
		
    }
	OnQuitCount++;
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnBeforeNavigate2 (IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
			CheckIFBOA(pvarURL,hwnd);
		

    }
	BeforeNavigate2Count++;
}
void STDMETHODCALLTYPE CHelloWorldBHO::OnNavigateComplete2(IDispatch *pDisp, VARIANT *pvarURL)
{
    // Retrieve the top-level window from the site.
    HWND hwnd;
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
    if (SUCCEEDED(hr))
    {
		CheckIFBOA(pvarURL,hwnd);


    }
	NavigateComplete2Count++;
}
//

