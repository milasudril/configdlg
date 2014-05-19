#ifdef __WAND__
target[name[test_model.h] type[include]]
dependency[test_model.o]
#endif

#ifndef CONFIGDLG_TESTMODEL_H
#define CONFIGDLG_TESTMODEL_H

#include <herbs/string/string.h>
#include <herbs/timet/timet.h>
#include <config/param_valueraw_info.h>
#include <config/param_group_info.h>
#include <config/param_valuemapped_info.h>
#include <mathext/valuemap.h>

namespace ConfigDlg
	{
	class TestModel
		{
		public:
			class InfMap:public MathExt::ValueMap<double>
				{
				public:				
					double forward(const double& x) const
						{
						return 1.0/(1.0-x);
						}
					
					double backward(const double& y) const
						{return 1.0-1.0/y;}
						
					MathExt::Interval<double> domain() const
						{
						return {0,1};
						}
					
					MathExt::Interval<double> range() const
						{
						return {1, 1.0/0.0};
						}
				};
		
			struct Parameters
				{
				Herbs::String name;
				Herbs::Timestamp date_birth;
				double mass;
				double length;
				};
			
			TestModel();
		
			Herbs::Array<Config::Paraminfo*> paramsGet();
		
		private:
			Parameters params;
			InfMap inf_map;
			Config::ParamValuerawInfo<Herbs::String> name_info;
			Config::ParamValuerawInfo<Herbs::Timestamp> datebirth_info;
			Config::ParamValuemappedInfo<double> mass_info;
			Config::ParamValuemappedInfo<double> length_info;
		};
	}

#endif
