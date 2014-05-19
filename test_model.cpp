#ifdef __WAND__
target[name[test_model.o] type[object]]
#endif

#include "test_model.h"

ConfigDlg::TestModel::TestModel():
 name_info     {STR("Namn"),      Config::Paraminfo::Type::STRING,   1,params.name,      Config::ParamValuerawInfo<Herbs::String>::UpdateMethod::NORMAL}
,datebirth_info{STR("Födelsedag"),Config::Paraminfo::Type::TIMESTAMP,2,params.date_birth,Config::ParamValuerawInfo<Herbs::Timestamp>::UpdateMethod::NORMAL}
,mass_info     {STR("Massa/kg")  ,3,params.mass,Config::ParamValueInfo<double>::UpdateMethod::CONTINOUS,inf_map}
,length_info     {STR("Längd/m")  ,4,params.length,Config::ParamValueInfo<double>::UpdateMethod::CONTINOUS,inf_map}
	{
	params.name=Herbs::String(STR("Terese Ljungborg"));
	params.date_birth=Herbs::Timestamp::fromNow();
	params.mass=60;
	params.length=1.7;
	}

Herbs::Array<Config::Paraminfo*> ConfigDlg::TestModel::paramsGet()
	{
	return {&name_info,&datebirth_info,&mass_info,&length_info,nullptr};
	}