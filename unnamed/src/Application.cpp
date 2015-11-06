#include "Application.hpp"

#include <cstdlib>
#include <iostream>

namespace unnamed {

static Application* instance = nullptr;

Application::Application() {
	instance = this;
	window_ = Window::New(Options()->windowOptions);
}

Application::~Application() {}

Application* Application::GetInstance() {
	return instance;
}

void Application::Exit() {
	OnExit();
	exit(0);
}
void Application::OnStart() {}
void Application::OnExit() {}
void Application::OnPause() {}
void Application::OnResume() {}
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
