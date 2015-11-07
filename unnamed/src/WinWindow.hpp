#pragma once

#ifdef __WIN32

#include "Window.hpp"

namespace unnamed {
    class WinWindow : public Window {
    public:
        WinWindow(WindowOptions options);
        virtual ~WinWindow();
        bool Create() override;
        void Run() override;
        void Close() override;
        int GetWidth() override;
        int GetHeight() override;
    };
}

#endif
