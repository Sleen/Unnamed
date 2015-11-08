#ifdef _WIN32

#include "WinWindow.hpp"

#include "Base/Log.hpp"
#include "Render/GL.hpp"
#include "Render/Transform.hpp"

using namespace me;

namespace unnamed {
    
    static WinWindow* window = nullptr;

    WinWindow::WinWindow(WindowOptions options) : Window(options) {
        window = this;
    }
    
    WinWindow::~WinWindow() {
        
    }
    
    bool WinWindow::Create() {
        WNDCLASSEX wc;
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = WinWindow::WndProc_Static;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = options_.title.c_str();

        BOOL result = SetProcessDPIAware();
        if (!result) {
            Log::W("SetProcessDPIAware failed!");
        }

        int titleHeight = GetSystemMetrics(SM_CYCAPTION);
        int paddedBorderWidth = GetSystemMetrics(SM_CXPADDEDBORDER);
        int borderWidth = GetSystemMetrics(SM_CXFRAME) + paddedBorderWidth;
        int borderHeight = GetSystemMetrics(SM_CYFRAME) + paddedBorderWidth;
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        width_ = options_.width;
        height_ = options_.height;
        borderWidth_ = borderWidth * 2;
        borderHeight_ = borderHeight * 2 + titleHeight;
        int width = width_ + borderWidth_;
        int height = height_ + borderHeight_;
        int x = (screenWidth - width) / 2;
        int y = (screenHeight - height) / 2;

        if (!RegisterClassEx(&wc)) {
            Log::E("register class failure");
            return false;
        }

        hwnd_ = CreateWindow(options_.title.c_str(), options_.title.c_str(),
            WS_VISIBLE | WS_OVERLAPPEDWINDOW,
            x, y, width, height,
            NULL, NULL, wc.hInstance, NULL);
        if (!hwnd_) {
            Log::E("Can not create window");
            return false;
        }

        static PIXELFORMATDESCRIPTOR pfdWnd =
        {
            sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
            1,                             // Structure version number.
            PFD_DRAW_TO_WINDOW |           // Property flags.
            PFD_SUPPORT_OPENGL |
            //PFD_SUPPORT_COMPOSITION |
            PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            24,                            // 24-bit color.
            0, 0, 0, 0, 0, 0,              // Not concerned with these.
            0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
            32,                            // 32-bit depth buffer.
            32, 0,                          // No stencil or aux buffer.
            PFD_MAIN_PLANE,                // Main layer type.
            0,                             // Reserved.
            0, 0, 0                        // Unsupported.
        };
        hdc_ = GetDC(hwnd_);
        
        int pixelformat = ChoosePixelFormat(hdc_, &pfdWnd);
        SetPixelFormat(hdc_, pixelformat, &pfdWnd);
        rc_ = wglCreateContext(hdc_);
        wglMakeCurrent(hdc_, rc_);

        GLenum err = glewInit();
        if (err != GLEW_OK){
            Log::E("GLEW Error: %s", glewGetErrorString(err));
        }

        Prepare(*this);

        wglSwapIntervalEXT(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0, 0, 0, 0);
    
        /*Viewport(0, 0, width_, height_);
        Log::I("viewport %d x %d", width_, height_);

        MatrixMode(PROJECTION_MATRIX);
        LoadIdentity();
        Ortho(0, width_, height_, 0, -1, 1);
        MatrixMode(MODELVIEW_MATRIX);
        LoadIdentity();*/

        return true;
    }
    
    void WinWindow::Run() {
        ShowWindow(hwnd_, SW_SHOW);

        UpdateWindow(hwnd_);

        shown_ = true;

        MSG msg;
        
        bool running = true;
        while (running)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else{
            //SendMessage(hwnd_, WM_PAINT, 0, 0);
        }

        OnClosed();
    }
    
    void WinWindow::Close() {
        PostQuitMessage(0);
    }
    
    int WinWindow::GetWidth() {
        return width_;
    }
    
    int WinWindow::GetHeight() {
        return height_;
    }

    void WinWindow::SetTitle(const std::string& title) {
        SetWindowText(window->hwnd_, title.c_str());
    }

    LRESULT CALLBACK WinWindow::WndProc_Static(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
        if (window) {
            return window->WndProc(hwnd, msg, wp, lp);
        }
        
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    LRESULT CALLBACK WinWindow::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
        switch (msg)
        {
        case WM_DESTROY:
            wglMakeCurrent(hdc_, NULL);
            wglDeleteContext(rc_);
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            SendMessage(hwnd, WM_PAINT, 0, 0);
            break;
        case WM_PAINT:
            if (shown_){
                wglMakeCurrent(hdc_, rc_);
                PushMatrix();
                glClear(GL_COLOR_BUFFER_BIT);

                Draw(*this);
                
                PopMatrix();
                glFlush();
                SwapBuffers(hdc_);
            }
            break;
        case WM_SIZE:
            //wglMakeCurrent(hdc, rc);
            //OnResize(Vector2(LOWORD(lp), HIWORD(lp)));
            width_ = LOWORD(lp);
            height_ = HIWORD(lp);

            Viewport(0, 0, width_, height_);
            Log::I("viewport %d x %d", width_, height_);

            MatrixMode(PROJECTION_MATRIX);
            LoadIdentity();
            Ortho(0, width_, height_, 0, -1, 1);
            MatrixMode(MODELVIEW_MATRIX);
            LoadIdentity();
            break;
        case WM_SIZING:
        {
           /* auto rect = (LPRECT)lp;
            width_ = rect->right - rect->left - borderWidth_;
            height_ = rect->bottom - rect->top - borderHeight_;

            Viewport(0, 0, width_, height_);
            Log::I("viewport %d x %d", width_, height_);

            MatrixMode(PROJECTION_MATRIX);
            LoadIdentity();
            Ortho(0, width_, height_, 0, -1, 1);
            MatrixMode(MODELVIEW_MATRIX);
            LoadIdentity();*/
            break;
        }
        case WM_ERASEBKGND:
            //wprintf(L"WM_ERASEBKGND\n");
            break;
            //case WM_SYSCOMMAND:
            //  DefWindowProc(hwnd, iMsg, wp, lp);
            //  break;
        // case WM_KEYDOWN:
        //     OnKeyEvent(KeyEventArgs(wp, KeyAction::Down));
        //     break;
        // case WM_KEYUP:
        //     OnKeyEvent(KeyEventArgs(wp, KeyAction::Up));
        //     break;
        // case WM_CHAR:
        //     OnKeyEvent(KeyEventArgs(wp, KeyAction::Press));
        //     break;
        // case WM_MOUSEMOVE:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), GetMouseButton(wp), MouseAction::Move));
        //     if (!trackingMouseLeave){       // 追踪鼠标离开事件
        //         TRACKMOUSEEVENT csTME;
        //         csTME.cbSize = sizeof (csTME);
        //         csTME.dwFlags = TME_LEAVE;
        //         csTME.hwndTrack = hwnd;
        //         TrackMouseEvent(&csTME);
        //         trackingMouseLeave = true;
        //     }
        //     break;
        // case WM_MOUSELEAVE:
        //     trackingMouseLeave = false;
        //     OnMouseLeave();
        //     break;
        // case WM_LBUTTONDOWN:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Left, MouseAction::Down));
        //     break;
        // case WM_RBUTTONDOWN:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Right, MouseAction::Down));
        //     break;
        // case WM_MBUTTONDOWN:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Middle, MouseAction::Down));
        //     break;
        // case WM_LBUTTONUP:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Left, MouseAction::Up));
        //     break;
        // case WM_RBUTTONUP:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Right, MouseAction::Up));
        //     break;
        // case WM_MBUTTONUP:
        //     OnMouseEvent(MouseEventArgs((short)LOWORD(lp),
        //         (short)HIWORD(lp), MouseButton::Middle, MouseAction::Up));
        //     break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
    }

}

#endif
