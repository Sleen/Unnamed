#include "Application.hpp"

#include <cstdlib>
#include <iostream>

namespace unnamed {

Application::Application() {
	window_ = Window::New(Options()->windowOptions);
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

}
