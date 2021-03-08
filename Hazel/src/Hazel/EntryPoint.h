#pragma once
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

#include"Core.h"
int main(int argc, char** argv)
{

	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!\n");
	int a = 5;
	HZ_INFO("hello! Var={0}\n", a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}


#endif