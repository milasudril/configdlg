#ifdef __WAND__
target[name[dialog.o] type[object]]
#endif

#include "dialog.h"
#include <herbs/stack/stack.h>

ConfigDlg::Dialog* ConfigDlg::Dialog::create(Gui::Gui& gui_obj,uint32_t style_0
	,uint32_t style_1,Gui::Window* parent)
	{
	return new Dialog(gui_obj,style_0,style_1,parent);
	}

void ConfigDlg::Dialog::init()
	{
	Gui::WindowCustom::init();
	}

void ConfigDlg::Dialog::onCommand(uint32_t event_status,uint32_t command_id,Window& source)
	{
	printf("Hello %S\n",source.titleGet().begin());
	source.valueUpdate();
	}
	
Vector::Vector2d<int> ConfigDlg::Dialog::componentsMove()
	{
	Vector::Vector2d<float> pos{0,2};
	
	auto c=components.begin();
	float y_prev=0;
	size_t i=0;
	while(c!=components.end())
		{
		c->first->sizeRelative(1,0);
		c->first->moveAbsolute({-1,-1},pos);
		auto size_res=c->first->sizeWindowGet();		
		pos.y+=1.05*size_res.y;
		
		if(i%2==1)
			{pos.y+=0.3*y_prev;}
		
		++i;
		++c;
		y_prev=size_res.y;
		}
	return Vector::Vector2d<int>{(int)pos.x,(int)pos.y};
	}

size_t ConfigDlg::Dialog::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case Gui::Window::MessageSize:
			{
			auto v=componentsMove();
			auto v2=sizeWindowGet();
			sizeAbsolute(std::max(v.x,v2.x),std::max(v.y,v2.y));
			}
			break;
		}
	return Gui::WindowCustom::onEvent(event_type,param_0,param_1);
	}
	
void ConfigDlg::Dialog::fontsSet(const Gui::Font* font_header
	,const Gui::Font* font_label
	,const Gui::Font* font_content)
	{
	Herbs::Stack<std::pair<decltype(components.begin())
		,decltype(components.end())>> nodes(16);
	
	if(components.begin()!=components.end())
		{nodes.push({components.begin(),components.end()});}
		
	while(nodes.depth()!=0)
		{
		auto c=nodes.pop();
		auto elem_current=c.first;
		switch(elem_current->second)
			{
			case ElementType::GROUP:
				{
				Dialog* dlg=(Dialog*)elem_current->first;
				if(dlg->components.begin()!=dlg->components.end())
					{nodes.push({dlg->components.begin(),dlg->components.end()});}
				}
				break;
	
			case ElementType::CONTROL:
				if(font_content!=nullptr)
					{elem_current->first->fontChangeRequest(*font_content);}
					
				if(elem_current+1!=c.second)
					{nodes.push({elem_current+1,c.second});}
				break;

			case ElementType::GROUP_LABEL:
				if(font_header!=nullptr)
					{elem_current->first->fontChangeRequest(*font_header);}
				
				if(elem_current+1!=c.second)
					{nodes.push({elem_current+1,c.second});}
				break;
			
			case ElementType::CONTROL_LABEL:
				if(font_label!=nullptr)
					{elem_current->first->fontChangeRequest(*font_label);}
				
				if(elem_current+1!=c.second)
					{nodes.push({elem_current+1,c.second});}
				break;
			}
		}
	}
