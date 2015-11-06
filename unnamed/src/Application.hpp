#pragma once
#include "Window.hpp"

namespace unnamed {

struct AppOptions {
	WindowOptions windowOptions;
};

class Application
{
public:
	Application();
	virtual ~Application();
	static Application* GetInstance();
	virtual AppOptions* Options();
	virtual void OnStart();
	virtual void OnExit();
	virtual void OnPause();
	virtual void OnResume();
	virtual void Run();
	void Exit();
	Window* GetWindow() { return window_; }

protected:
	Window* window_;
};

}
