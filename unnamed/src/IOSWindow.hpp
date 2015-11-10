#pragma once

#include "Target.hpp"

#if UNNAMED_TARGET_IOS

#include "Window.hpp"

namespace unnamed {

struct IOSWindowContext;
    
class IOSWindow : public Window {
public:
    IOSWindow(WindowOptions options);
    virtual ~IOSWindow();
	bool Create() override;
	void Run() override;
	void Close() override;
    int GetWidth() override;
    int GetHeight() override;
    void SetTitle(const std::string& title) override;

//private:
    IOSWindowContext* context_ = nullptr;
};

}

#endif
