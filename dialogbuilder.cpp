#ifdef __WAND__
target[name[dialogbuilder.o] type[object]]
#endif

#include "dialogbuilder.h"
#include "dialog.h"

#include <config/param_valuemapped.h>
#include <config/param_flagset.h>
#include <config/param_intnamed.h>
#include <config/param_group.h>
#include <config/param_valueraw.h>

#include <herbs/stringformat/stringformat.h>
#include <herbs/intformat/intformat.h>
#include <herbs/floatformat/floatformat.h>
#include <herbs/path/path.h>
#include <herbs/timet/timet.h>

#include <gui/valueinput.h>
#include <gui/label.h>
#include <gui/datetime_val.h>
#include <gui/fader_impl.h>

namespace
	{
	Gui::Label* labelCreate(Gui::Gui& gui_obj,ConfigDlg::Dialog& dlg
		,const Config::Paramobj& param)
		{
		auto obj=Gui::Label::create(gui_obj,Gui::Window::StyleEx_transparent
			,Gui::Window::StyleChild|Gui::Window::StyleVisible
			,&dlg);
		obj->titleSet(param.nameGet().begin());
		
		return obj;
		}
	}

ConfigDlg::DialogBuilder::DialogBuilder(Gui::Gui& gui,Gui::Window* parent):
	gui_obj(gui),m_parent(parent),root(nullptr){}

void ConfigDlg::DialogBuilder::init()
	{ConfigDlg::Dialog::init();}

void ConfigDlg::DialogBuilder::create(Config::ParamGroup& group)
	{
	Dialog* mainwin;
	if(group.groupGet()==nullptr)
		{
		Gui::Window* win_root=m_parent;
		mainwin=Dialog::create(gui_obj,0,0,win_root);
		mainwin->popup();
		mainwin->titleSet(group.nameGet().begin());
		}
	else
		{
		Dialog* win_root=nullptr;
		auto p=m_windows.find(group.groupGet());
		win_root=p->second;
		
		auto label=labelCreate(gui_obj,*win_root,group);
		win_root->childAppend({label,ConfigDlg::Dialog::ElementType::GROUP_LABEL});
		
		mainwin=Dialog::create(gui_obj,Gui::Window::StyleEx_clientedge
			|Gui::Window::StyleEx_controlparent
			,Gui::Window::StyleVisible|Gui::Window::StyleChild,win_root);
		mainwin->titleSet(STR("GROUP"));
		win_root->childAppend({mainwin,Dialog::ElementType::GROUP});
		}
	if(root==nullptr)
		{root=mainwin;}
	m_windows.insert({&group,mainwin});
	}
	
void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<int32_t>& param)
	{create_valmapped(param);}

void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<int64_t>& param)
	{create_valmapped(param);}

void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<uint32_t>& param)
	{create_valmapped(param);}

void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<uint64_t>& param)
	{create_valmapped(param);}

void ConfigDlg::DialogBuilder::create(Config::ParamIntnamed<uint32_t>& param)
	{}

void ConfigDlg::DialogBuilder::create(Config::ParamIntnamed<uint64_t>& param)
	{}

void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<float>& param)
	{create_valmapped(param);}

void ConfigDlg::DialogBuilder::create(Config::ParamValuemapped<double>& param)
	{create_valmapped(param);}
	
template<class T>
void ConfigDlg::DialogBuilder::create_valmapped(Config::ParamValuemapped<T>& param)
	{
	auto p=m_windows.find(param.groupGet());
	auto win_root=p->second;
	auto label=labelCreate(gui_obj,*win_root,param);
	win_root->childAppend({label,ConfigDlg::Dialog::ElementType::CONTROL_LABEL});
	
	switch(param.updateMethodGet())
		{
		case Config::ParamValueInfo<T>::UpdateMethod::NORMAL:
			{
			auto obj=Gui::ValueInput<T>::create(gui_obj,0
				,Gui::Window::StyleChild|Gui::Window::StyleVisible
				|Gui::Window::StyleBorder|Gui::Window::StyleTabstop,win_root
				,param.valueGet());
		
			win_root->childAppend({obj,Dialog::ElementType::CONTROL});
			obj->displayUpdate();
			}
			break;
		
		case Config::ParamValueInfo<T>::UpdateMethod::CONTINOUS:
			{
			auto obj=Gui::FaderImpl<T>::create(gui_obj,0
				,Gui::Window::StyleChild|Gui::Window::StyleVisible
				|Gui::Window::StyleBorder|Gui::Window::StyleTabstop,win_root
				,param.valueMapGet(),param.valueGet());
		
			win_root->childAppend({obj,Dialog::ElementType::CONTROL});
			obj->displayUpdate();
			}
			break;
		}
	}
	
void ConfigDlg::DialogBuilder::create(Config::ParamValueraw<Herbs::Timestamp>& param)
	{
	auto p=m_windows.find(param.groupGet());
	auto win_root=p->second;
	auto label=labelCreate(gui_obj,*win_root,param);
	win_root->childAppend({label,ConfigDlg::Dialog::ElementType::CONTROL_LABEL});
	
	auto obj=Gui::DatetimeVal::create(gui_obj,0
		,Gui::Window::StyleChild|Gui::Window::StyleVisible
			|Gui::Window::StyleBorder|Gui::Window::StyleTabstop,win_root
		,param.valueGet());
		
	win_root->childAppend({obj,Dialog::ElementType::CONTROL});
	obj->displayUpdate();
	}

void ConfigDlg::DialogBuilder::create(Config::ParamFlagset<uint32_t>& param)
	{}

void ConfigDlg::DialogBuilder::create(Config::ParamFlagset<uint64_t>& param)
	{}

void ConfigDlg::DialogBuilder::create(Config::ParamValueraw<Herbs::String>& param)
	{
	auto p=m_windows.find(param.groupGet());
	auto win_root=p->second;

	auto label=labelCreate(gui_obj,*win_root,param);
	win_root->childAppend({label,ConfigDlg::Dialog::ElementType::CONTROL_LABEL});
	
	auto obj=Gui::ValueInput<Herbs::String>::create(gui_obj,0
		,Gui::Window::StyleChild|Gui::Window::StyleVisible
			|Gui::Window::StyleBorder|Gui::Window::StyleTabstop,win_root
		,param.valueGet());
		
	win_root->childAppend({obj,Dialog::ElementType::CONTROL});
	obj->displayUpdate();
	}

void ConfigDlg::DialogBuilder::create(Config::ParamValueraw<Herbs::Path>& param)
	{}

