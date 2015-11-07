#include "Application.hpp"

#include "WinWindow.hpp"
#include "OSXWindow.hpp"

#include <cstdlib>
#include <iostream>

namespace unnamed {

Application::Application() {
	window_ = CreateWindow();
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
    
    Window* Application::CreateWindow() {
#ifdef __WIN32
        return new WinWindow(Options()->windowOptions);
#elif defined __APPLE__
        return new OSXWindow(Options()->windowOptions);
#endif
    }

}
