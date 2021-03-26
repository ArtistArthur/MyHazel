# MyHazel

## Setup Entry Point
游戏引擎作为一个动态库，也需要一个`main()`入口，在这里我们设置这个入口：  
* `Application`类给用户提供了一个接口`Application* CreateApplication();`用户自定义这个接口，返回一个类对象给引擎
* `EntryPoint.h`调用`CreateApplication();`获得类对象，客户程序就是这样进入引擎的
* `Core.h`定义相关宏，进行跨平台或者灵活性操作，`Application.h`应该包含它
* `Hazel.h`包含引擎的相关头文件，用户可以仅仅包含这一个头文件，就可以使用引擎的所有内容，更方便，就不需要通过相对路径包含了
* `Sandbox.cpp`是用户编写游戏的部分
* `Sandbox`类通过继承`Application`类来使用引擎

## Logging system
我们需要一个日志系统来记录我们的引擎做了什么，正在做什么等等，以了解我们的引擎：  
* 引用日志库`spdlog`，把它作为一个子模块嵌在引擎里
  * `git submodule add https://github.com/gabime/spdlog Hazel/vendor/spdlog`
  * 以后的许多子模块都存放在`Hazel/vendor/`下

但是为了减少依赖性，我们需要封装`spdlog`的API，以防以后改变日志模块时需要重写代码
* 通过宏封装
* 定义自己的Log类
  * 定义一个引擎的`CoreLogger`对象，一个应用的`ClientLogger`对象，以及获得他们的`GetCoreLogger();`和`GetClientLogger();`
  * 一个初始化函数`Init();`
  * 一系列宏来输出不同类型的Log：`trace info warn error fatal`等

## Premake
为了可以不仅仅在win-vs上构建项目，可以支持Linux，macos等平台上构建项目，加入premake来构建项目，不选cmake的原因是cmake太复杂，并且没必要的复杂。  
premake用lua来编写。  
* `workspace`是类似solution的东西，是你整个项目的工作区，这里叫`Hazel`  
  * `architecture`是x64，x86等
  * `configurations`代表代码版本，比如有`Debug` `Release`（Debug的进阶版，去除了Debug的符号表等，开启了优化等，但是日志等还是存在， `Dist`（完全的发行版，日志等任何调试信息都去除，用户版本）
* `project`对应与主目录下的Hazel目录，和Sandbox平行的，是项目名称
  *  Hazel的位置：与premake在同一目录下，因此直接是`Hazel`
  *  `kind`标识这个项目最终产生什么文件，这里是`SharedLib`
  *  `language`标识项目的语言，这里是C++
  *  `target`是可执行文件的位置
  *  `obj`是目标文件的位置
  *  `files`是我们需要包含进去的文件，C++文件，头文件等
     *  `"%{prj.name}/src/**.h"`表示在Hazel下的sr下的头文件，两个星代表递归包含
     *  `"%{prj.name}/src/**.cpp"`类似
  * `include`表示要包含的头文件，要包含的是指使用了其他模块，需要包含的目录
    * 使用了`spdlog`模块，因此要包含`%{prj.name}/vendor/spdlog/include`
## EventSystem planning
Application是Hazel主要的文件，里面有许多类  
* Window类是我们的窗口
  * renderer
  * resize、 close
    * 收到一个event
    * communicate with Application，window不应该知道Application的存在
      * window里发生一个event 通过回调函数传递给Application
      * Application在创建window的时候同时set call back，当Window产生事件的时候，就检查是否有相应的callback存在，

## EventSystem 
初始版本的Event是阻塞的，意味着当事件发生时，需要马上处理它。一个更好的策略是"buffer events in an bus and process them during the "event" part of the update stage."  
我们需要一个`enum class EventType`去表示事件的类型：
* 空类型`None`
* 窗口事件：`WindowClose`,`WindowResize`, `WindowFocus`, `WindowLostFocus`, `WindowMoved`
* 应用事件：`AppTick`, `AppUpdate`, `AppRender`
* 键盘事件：`KeyPressed`, `KeyReleased`
* 鼠标事件：`MouseButtonPressed`, `MouseButtonReleased`, `MouseMoved`, `MouseScrolled`

`EventCategory`记录事件的类别，而不用一个一个去判断是某个特定的事件。  
