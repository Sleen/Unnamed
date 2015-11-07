#pragma once

#ifdef __WIN32

#include "Window.hpp"

#include <Windows.h>

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

    private:
        HWND hwnd_ = nullptr;
        HDC hdc_ = nullptr;
        HGLRC rc_ = nullptr;
        bool trackingMouseLeave_ = false;
        bool shown_ = false;
        int width_ = 0;
        int height_ = 0;
        int borderWidth_ = 0;
        int borderHeight_ = 0;

        static LRESULT CALLBACK WndProc_Static(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
        LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    };
}

#endif
