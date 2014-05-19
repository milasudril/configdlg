#ifdef __WAND__
target[name[test_host.h] type[include]]
dependency[test_host.o]
#endif

#ifndef CONFIGDLG_TESTHOST_H
#define CONFIGDLG_TESTHOST_H

#include "dialogbuilder.h"
#include "test_model.h"

#include <gui/font.h>
#include <gui/gui.h>

namespace ConfigDlg
	{
	class TestHost:public Gui::Gui
		{
		public:
			TestHost(Herbs::LogWriter& log);
		
		private:
			DialogBuilder builder;
			TestModel model;
			::Gui::Font font_header;
			::Gui::Font font_label;
			::Gui::Font font_content;
		};
	}

#endif

