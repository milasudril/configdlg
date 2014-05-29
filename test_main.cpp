#ifdef __WAND__
target[name[configdlg_test.exe] type[application] platform[;Windows]]
target[name[configdlg_test] type[application]]
#endif

#include "test_host.h"
#include <herbs/maindefault/maindefault.h>

Herbs::Application* Herbs::Application::instanceCreate(Herbs::LogWriter& log
	,Herbs::Directory&& options)
	{
	return new ConfigDlg::TestHost(log);
	}