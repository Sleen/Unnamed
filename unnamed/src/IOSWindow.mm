#include "Target.hpp"

#if UNNAMED_TARGET_IOS

#include "IOSWindow.hpp"
#include "Application.hpp"

#include "Render/Graphics.hpp"
#include "Math/Math.hpp"

#import  <UIKit/UIKit.h>
#import  <GLKit/GLKit.h>

#define CHECK_MASK(value, mask) (((value) & (mask)) == (mask))

using namespace unnamed;
using namespace me;

static IOSWindow* instance = nullptr;

namespace unnamed {
    
    struct IOSWindowContext {
        UIWindow* window = nullptr;
    };

}

@interface GLViewController : GLKViewController
{
    IOSWindow* window_;
}

- (instancetype)initWithIOSWindow:(IOSWindow *)window;

@end

@implementation GLViewController

- (instancetype)initWithIOSWindow:(unnamed::IOSWindow *)window {
    if (self = [super init]) {
        window_ = window;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    GLKView *view = (GLKView *)self.view;
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    // Configure renderbuffers created by the view
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    
    // Enable multisampling
    //view.drawableMultisample = GLKViewDrawableMultisample4X;
    
    self.preferredFramesPerSecond = 60;
    
    [EAGLContext setCurrentContext:view.context];
    
    int width = view.frame.size.width * [UIScreen mainScreen].scale;
    int height = view.frame.size.height * [UIScreen mainScreen].scale;
    
    Viewport(0, 0, width, height);
    NSLog(@"viewport %d x %d", width, height);
    
    MatrixMode(PROJECTION_MATRIX);
    LoadIdentity();
    Ortho(0, width, height, 0, -1, 1);
    MatrixMode(MODELVIEW_MATRIX);
    LoadIdentity();
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    window_->Prepare(*window_);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClear(GL_COLOR_BUFFER_BIT);
    
    PushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    
    window_->Draw(*window_);
    
    PopMatrix();
}

@end

@interface AppDelegate : NSObject  <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [UIApplication sharedApplication].statusBarHidden = YES;
    _window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    instance->context_->window = _window;
    _window.rootViewController = [[GLViewController alloc] initWithIOSWindow:instance];
    [_window makeKeyAndVisible];
    return YES;
}

@end

namespace unnamed {

IOSWindow::IOSWindow(WindowOptions options) : Window(options) {
    context_ = new IOSWindowContext();
}

IOSWindow::~IOSWindow() {
    if (context_) {
        delete context_;
    }
}

bool IOSWindow::Create() {
    instance = this;
//    @autoreleasepool {
//        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
//        
//        GLView *view = [[GLView alloc] initWithFrame:window.bounds window:this];
//        if (!view) {
//            return false;
//        }
//
//        window.rootViewController = [[UIViewController alloc] init];
//        window.rootViewController.view = view;
//        [window makeKeyAndVisible];
//        [UIApplication sharedApplication].delegate = view;
//        context_->window = window;
//    }

    return true;
}

void IOSWindow::Run() {
    @autoreleasepool {
        //[AppDelegate load];
        UIApplicationMain(0, nil, nil, NSStringFromClass([AppDelegate class]));
    }
    
    OnClosed();
}

void IOSWindow::Close() {
    
}

int IOSWindow::GetWidth() {
    return context_->window.bounds.size.width * [UIScreen mainScreen].scale;
}

int IOSWindow::GetHeight() {
    return context_->window.bounds.size.height * [UIScreen mainScreen].scale;
}

void IOSWindow::SetTitle(const std::string& title) {
    context_->window.rootViewController.title = [NSString stringWithUTF8String:title.c_str()];
}

}

#endif
