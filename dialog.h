#ifdef __WAND__
target[name[dialog.h] type[include]]
dependency[dialog.o]
#endif

#ifndef CONFIGDLG_DIALOG_H
#define CONFIGDLG_DIALOG_H

#include <gui/window-custom.h>

namespace Gui
	{
	class Font;
	}

namespace ConfigDlg
	{
	class Dialog:public Gui::WindowCustom
		{
		public:
			enum class ElementType:uint32_t{GROUP,CONTROL,GROUP_LABEL,CONTROL_LABEL};
			
			static void init();
		
			static Dialog* create(Gui::Gui& gui_obj,uint32_t style_0,uint32_t style_1
				,Gui::Window* parent);
			
			void childAppend(const std::pair<Window*,ElementType>& obj)
				{components.append(obj);}
			
			void onCommand(uint32_t event_status,uint32_t command_id,Window& source);
			
			Vector::Vector2d<int> componentsMove();
			
			size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			void fontsSet(const Gui::Font* font_header
				,const Gui::Font* font_label
				,const Gui::Font* font_content);
			
		private:
			Dialog(Gui::Gui& gui_obj,uint32_t style_0,uint32_t style_1,Gui::Window* parent):
				Gui::WindowCustom(gui_obj,style_0,style_1,parent)
				{}
			
			Herbs::Array<std::pair<Gui::Window*,ElementType>> components;
		};
	}

#endif

