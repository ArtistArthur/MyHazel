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
	//�ṩ���û���һ���ӿڣ��û�ͨ������ӿڷ����Լ��������
	Application* CreateApplication();

}