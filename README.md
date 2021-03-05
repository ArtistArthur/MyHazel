# MyHazel

## Setup Entry Point
游戏引擎作为一个动态库，也需要一个`main()`入口，在这里我们设置这个入口：  
* `Application`类给用户提供了一个接口`Application* CreateApplication();`用户自定义这个接口，返回一个类对象给引擎
* `EntryPoint.h`调用`CreateApplication();`获得类对象，客户程序就是这样进入引擎的
* `Core.h`定义相关宏，进行跨平台或者灵活性操作，`Application.h`应该包含它
* `Hazel.h`包含引擎的相关头文件，用户可以仅仅包含这一个头文件，就可以使用引擎的所有内容，更方便，就不需要通过相对路径包含了
* `Sandbox.cpp`是用户编写游戏的部分
* `Sandbox`类通过继承`Application`类来使用引擎