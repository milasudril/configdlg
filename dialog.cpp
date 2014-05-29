#ifdef __WAND__
target[name[dialog.o] type[object]]
#endif

#include "dialog.h"
#include <herbs/stack/stack.h>
#include <gui/dialog.h>
#include <gui/button.h>

ConfigDlg::Dialog* ConfigDlg::Dialog::create(Gui::Gui& gui_obj,uint32_t style_0
	,uint32_t style_1,Gui::Window* parent)
	{
	return new Dialog(gui_obj,style_0,style_1,parent);
	}

void ConfigDlg::Dialog::init()
	{
	Gui::WindowCustom::init();
	}

size_t ConfigDlg::Dialog::onCommand(uint32_t event_status,uint32_t command_id,Window& source)
	{
	switch(command_id)
		{
		case Gui::Dialog::MESSAGESTATUS_OK:
		case Gui::Dialog::MESSAGESTATUS_CANCEL:
		case COMMAND_APPLY:
			{
			Gui::Window* parent=parentGet();
			
			if(parent!=nullptr)
				{
				parent->onCommand(event_status,command_id,*this);
				return 0;
				}
			}
			break;
		default:
			source.valueUpdate();
		}

	return 0;
	}

void ConfigDlg::Dialog::buttonsAdd()
	{
	ok=Gui::Button::create(m_gui,0
		,Gui::Window::StyleChild|Gui::Window::StyleVisible
		|Gui::Window::StyleTabstop,this);
	ok->idSet( Gui::Dialog::MESSAGESTATUS_OK);
	ok->titleSet(STR("OK"));

	cancel=Gui::Button::create(m_gui,0
		,Gui::Window::StyleChild|Gui::Window::StyleVisible
		|Gui::Window::StyleTabstop,this);
	cancel->idSet( Gui::Dialog::MESSAGESTATUS_CANCEL);
	cancel->titleSet(STR("Avbryt"));
	
	apply=Gui::Button::create(m_gui,0
		,Gui::Window::StyleChild|Gui::Window::StyleVisible
		|Gui::Window::StyleTabstop,this);
	apply->idSet(COMMAND_APPLY);
	apply->titleSet(STR("Verkställ"));
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
		case Gui::Window::MessageActivate:
			{
			if(param_0==0)          
				{dialogDeactivate();}
            else
				{dialogActivate();}
			return 0;
			}
			break;
			
		case Gui::Window::MessageSize:
			{
			auto v=componentsMove();
			auto v2=sizeWindowGet();
			
			if(ok!=nullptr) //If one button is there, so is the others
				{
				ok->sizeAbsolute(0,0);				
				cancel->sizeAbsolute(0,0);
				apply->sizeAbsolute(0,0);
				
				Vector::Vector2d<int> sizes[]=
					{
					 ok->sizeWindowGet()
					,cancel->sizeWindowGet()
					,apply->sizeWindowGet()
					};
				
				Vector::Vector2d<int> maxmax={0,0};
				for(int k=0;k<3;++k)
					{
					if(sizes[k].x>maxmax.x || sizes[k].y>maxmax.y)
						{maxmax=sizes[k];}
					}
					
				ok->sizeAbsolute(maxmax.x,maxmax.y);				
				cancel->sizeAbsolute(maxmax.x,maxmax.y);
				apply->sizeAbsolute(maxmax.x,maxmax.y);
				
				cancel->moveAbsolute({0,-1},{0.5f*v2.x + 0.5f,float(v.y)});
				auto p=cancel->positionAbsoluteGet();
				ok->moveAbsolute({1+1.0/8,-1},{float(p.x),float(v.y)});
				p+=maxmax;
				apply->moveAbsolute({-(1+1.0/8),-1},{float(p.x),float(v.y)});
				}
			
			sizeAbsolute(std::max(v.x,v2.x),std::max(v.y,v2.y));
			}
			break;
			
		case Gui::Window::MessageClose:
			{
			Gui::Window* parent=parentGet();
			if(parent!=nullptr)
				{
				parent->onCommand(0,Gui::Dialog::MESSAGESTATUS_CANCEL,*this);
				return 0;
				}
			}
			
		}
	return Gui::WindowCustom::onEvent(event_type,param_0,param_1);
	}
	
void ConfigDlg::Dialog::fontsSet(const Gui::Font* font_header
	,const Gui::Font* font_label
	,const Gui::Font* font_content)
	{
	
	if(ok!=nullptr) //If one button is there, so is the others
		{
		ok->fontChangeRequest(*font_content);
		cancel->fontChangeRequest(*font_content);
		apply->fontChangeRequest(*font_content);
		}
	
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
				if(elem_current+1!=c.second)
					{nodes.push({elem_current+1,c.second});}
				if(dlg->components.begin()!=dlg->components.end())
					{
					nodes.push({dlg->components.begin(),dlg->components.end()});
					}
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
