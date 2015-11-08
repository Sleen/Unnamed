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
        virtual void OnDraw() {}
        virtual void OnUpdate() {}
        virtual void OnPrepare() {}
        virtual void Run();
        virtual Window* SetupWindow();
        Window* GetWindow() { return window_; }

    private:
        Window* window_;
    };

}
