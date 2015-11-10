#include "Application.hpp"

#include "WinWindow.hpp"
#include "OSXWindow.hpp"
#include "IOSWindow.hpp"
#include "Time.hpp"
#include "Target.hpp"

#include <cstdlib>
#include <iostream>

namespace unnamed {

Application::Application() {
	window_ = SetupWindow();
    window_->Draw += [this](Window&) { Time::UpdateTime(); OnDraw(); };
    window_->Prepare += [this](Window&){ OnPrepare(); };
}

Application::~Application() {}

void Application::Run() {
	if (window_->Create()) {
		window_->Run();
	} else {
		std::cout << "Error: failed to create window." <<std::endl;
	}
}

AppOptions* Application::Options() {
	static AppOptions* options = nullptr;
	if (options == nullptr) {
		options = new AppOptions();
		options->windowOptions = {"Test Window", 800, 600, false, false};
	}
	return options;
}
    
    Window* Application::SetupWindow() {
#if UNNAMED_TARGET_WINDOWS
        return new WinWindow(Options()->windowOptions);
#elif UNNAMED_TARGET_OSX
        return new OSXWindow(Options()->windowOptions);
#elif UNNAMED_TARGET_IOS
        return new IOSWindow(Options()->windowOptions);
#endif
    }

}
