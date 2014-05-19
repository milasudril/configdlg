#ifdef __WAND__
target[name[test_host.o] type[object]]
#endif

#include "test_host.h"
#include "dialog.h"
#include <config/paramset.h>

ConfigDlg::TestHost::TestHost(Herbs::LogWriter& log):
	Gui::Gui(log)
	,builder(*this,nullptr)
	,font_header(::Gui::Font::Element::CAPTION)
	,font_label(::Gui::Font::Element::CAPTION_SMALL)
	,font_content(::Gui::Font::Element::WIDGET)
	
	{
	Dialog::init();
	auto params=model.paramsGet();
	Config::Paramset ps(params.begin());
	ps.uiCreate(builder);
	
	Dialog* win_root=builder.rootGet();
	win_root->fontsSet(&font_header,&font_label,&font_content);
	win_root->sizeRelative(0.5,0.5);
	win_root->moveRelative({0,0},{0.5,0.5});
	win_root->show(::Gui::Window::DisplayNormal);
	}