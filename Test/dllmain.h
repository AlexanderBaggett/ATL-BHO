// dllmain.h : Declaration of module class.

class CTestModule : public ATL::CAtlDllModuleT< CTestModule >
{
public :
	DECLARE_LIBID(LIBID_TestLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEST, "{5D82B29A-2062-418B-AFA1-5933B6D131BC}")
};

extern class CTestModule _AtlModule;
