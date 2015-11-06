#pragma once
#ifdef __APPLE__

#include "Window.hpp"

#include <Cocoa/Cocoa.h>

namespace unnamed {

class OSXWindow : public Window {
public:
	OSXWindow(WindowOptions options) : Window(options) { }
	bool Create();
	void Run();
	void Close();
    int GetWidth();
    int GetHeight();

//private:
	NSApplication* app_ = nullptr;
	NSWindow* window_ = nullptr;
};

}

#endif
