#pragma once
#include "ConsoleApplication.hpp"
#include "Window.hpp"

namespace unnamed {

struct AppOptions {
	WindowOptions windowOptions;
};

    class Application : public ConsoleApplication
    {
    public:
        Application();
        virtual ~Application();
        virtual AppOptions* Options();
        virtual void OnPause() {}
        virtual void OnResume() {}
        virtual void Run();
        Window* GetWindow() { return window_; }

    protected:
        Window* window_;
    };

}
