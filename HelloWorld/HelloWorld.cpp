// HelloWorld.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "HelloWorld.h"


class CHelloWorldModule : public CAtlDllModuleT< CHelloWorldModule >
{
public :
	DECLARE_LIBID(LIBID_HelloWorldLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELLOWORLD, "{E908D2F6-1C91-4900-8FF7-B677262A8A5A}")

};

CHelloWorldModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif


// DLL Entry Point
//neeed to grab this HINSTANCE to create our window.
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
    {
		hDLL = hInstance;
        DisableThreadLibraryCalls(hInstance);
    }
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif



// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

