#pragma once
#include"Core.h"

namespace Hazel{
	class  HAZEL_API Application
	{
	public:
		Application();
	virtual ~Application();
		void Run();
	};
	//to be defined in client
	//提供给用户的一个接口，用户通过这个接口返回自己定义的类
	Application* CreateApplication();

}