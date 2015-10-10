//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#include "isum.h"
#include "class_ids.h"

#include "plugin/loader.h"

  #include <iostream>
#include "common/filewatcher.h"

int main()
{
	try	{
		Boss::Loader Ldr("Registry.xml", "../lib/" MAKE_MODULE_NAME("service_registry"),
				"../lib/" MAKE_MODULE_NAME("class_factory"));
		int stub = 0;
		int stub1 = 1;
		int stub2 = 2;
		auto Obj = Boss::CreateObject<MyNs::ISum>(MyNs::Service::Id::Sum);
		int Res = 0;
		if (Obj->CalcSum(10, 20, &Res))
			std::cout << "Failed to calc sum." << std::endl;
		std::cout << "Sum: " << Res << std::endl;
	}
	catch (std::exception const &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
