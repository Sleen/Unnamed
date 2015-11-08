#pragma once

#ifdef __APPLE__

#include "Window.hpp"

namespace unnamed {

struct OSXWindowContext;
    
class OSXWindow : public Window {
public:
    OSXWindow(WindowOptions options);
    virtual ~OSXWindow();
	bool Create() override;
	void Run() override;
	void Close() override;
    int GetWidth() override;
    int GetHeight() override;
    void SetTitle(const std::string& title) override;

private:
    OSXWindowContext* context_ = nullptr;
};

}

#endif
