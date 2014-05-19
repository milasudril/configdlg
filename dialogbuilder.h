#ifdef __WAND__
target[name[dialogbuilder.h] type[include] ]
dependency[dialogbuilder.o]
#endif

#ifndef CONFIGDLG_DIALOGBUILDER_H
#define CONFIGDLG_DIALOGBUILDER_H

#include <config/uiprovider.h>
#include <map>

namespace Gui
	{
	class Gui;
	class Window;
	}

namespace ConfigDlg
	{
	class Dialog;
	
	class DialogBuilder:public Config::UIProvider
		{
		public:
			static void init();
		
			DialogBuilder(Gui::Gui& gui,Gui::Window* parent);
			
			void create(Config::ParamGroup& group);
			void create(Config::ParamValuemapped<int32_t>& param);
			void create(Config::ParamValuemapped<int64_t>& param);
			void create(Config::ParamValuemapped<uint32_t>& param);
			void create(Config::ParamValuemapped<uint64_t>& param);
			void create(Config::ParamIntnamed<uint32_t>& param);
			void create(Config::ParamIntnamed<uint64_t>& param);
			void create(Config::ParamValuemapped<float>& param);
			void create(Config::ParamValuemapped<double>& param);
			void create(Config::ParamValueraw<Herbs::Timestamp>& param);
			void create(Config::ParamFlagset<uint32_t>& param);
			void create(Config::ParamFlagset<uint64_t>& param);
			void create(Config::ParamValueraw<Herbs::String>& param);
			void create(Config::ParamValueraw<Herbs::Path>& param);
			
			Dialog* rootGet() const
				{return root;}
				
		private:
			Gui::Gui& gui_obj;
			Gui::Window* m_parent;
			Dialog* root;
			std::map<Config::ParamGroup*,Dialog*> m_windows;
			
			template<class T>
			void create_valmapped(Config::ParamValuemapped<T>& param);
		};
	}

#endif
