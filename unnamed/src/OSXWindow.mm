#include "Target.hpp"

#if UNNAMED_TARGET_OSX

#include "OSXWindow.hpp"

#include "Render/Graphics.hpp"
#include "Math/Math.hpp"

#include <OpenGL/gl.h>

#import  <Cocoa/Cocoa.h>
#import  <Carbon/Carbon.h>

#define CHECK_MASK(value, mask) (((value) & (mask)) == (mask))

using namespace unnamed;
using namespace me;

Keys getKey(int keyCode) {
    switch (keyCode) {
    case kVK_ANSI_A:
        return Keys::A;
    case kVK_ANSI_S:
        return Keys::S;
    case kVK_ANSI_D:
        return Keys::D;
    case kVK_ANSI_F:
        return Keys::F;
    case kVK_ANSI_H:
        return Keys::H;
    case kVK_ANSI_G:
        return Keys::G;
    case kVK_ANSI_Z:
        return Keys::Z;
    case kVK_ANSI_X:
        return Keys::X;
    case kVK_ANSI_C:
        return Keys::C;
    case kVK_ANSI_V:
        return Keys::V;
    case kVK_ANSI_B:
        return Keys::B;
    case kVK_ANSI_Q:
        return Keys::Q;
    case kVK_ANSI_W:
        return Keys::W;
    case kVK_ANSI_E:
        return Keys::E;
    case kVK_ANSI_R:
        return Keys::R;
    case kVK_ANSI_Y:
        return Keys::Y;
    case kVK_ANSI_T:
        return Keys::T;
    case kVK_ANSI_1:
        return Keys::Num1;
    case kVK_ANSI_2:
        return Keys::Num2;
    case kVK_ANSI_3:
        return Keys::Num3;
    case kVK_ANSI_4:
        return Keys::Num4;
    case kVK_ANSI_6:
        return Keys::Num6;
    case kVK_ANSI_5:
        return Keys::Num5;
    case kVK_ANSI_Equal:
        return Keys::Equal;
    case kVK_ANSI_9:
        return Keys::Num9;
    case kVK_ANSI_7:
        return Keys::Num7;
    case kVK_ANSI_Minus:
        return Keys::Minus;
    case kVK_ANSI_8:
        return Keys::Num8;
    case kVK_ANSI_0:
        return Keys::Num0;
    case kVK_ANSI_RightBracket:
        return Keys::RightBracket;
    case kVK_ANSI_O:
        return Keys::O;
    case kVK_ANSI_U:
        return Keys::U;
    case kVK_ANSI_LeftBracket:
        return Keys::LeftBracket;
    case kVK_ANSI_I:
        return Keys::I;
    case kVK_ANSI_P:
        return Keys::P;
    case kVK_ANSI_L:
        return Keys::L;
    case kVK_ANSI_J:
        return Keys::J;
    case kVK_ANSI_Quote:
        return Keys::Quote;
    case kVK_ANSI_K:
        return Keys::K;
    case kVK_ANSI_Semicolon:
        return Keys::Semicolon;
    case kVK_ANSI_Backslash:
        return Keys::Backslash;
    case kVK_ANSI_Comma:
        return Keys::Comma;
    case kVK_ANSI_Slash:
        return Keys::Slash;
    case kVK_ANSI_N:
        return Keys::N;
    case kVK_ANSI_M:
        return Keys::M;
    case kVK_ANSI_Period:
        return Keys::Period;
    case kVK_ANSI_Grave:
        return Keys::Grave;
    case kVK_ANSI_KeypadDecimal:
        return Keys::KeypadDecimal;
    case kVK_ANSI_KeypadMultiply:
        return Keys::KeypadMultiply;
    case kVK_ANSI_KeypadPlus:
        return Keys::KeypadPlus;
    case kVK_ANSI_KeypadClear:
        return Keys::KeypadClear;
    case kVK_ANSI_KeypadDivide:
        return Keys::KeypadDivide;
    case kVK_ANSI_KeypadEnter:
        return Keys::KeypadEnter;
    case kVK_ANSI_KeypadMinus:
        return Keys::KeypadMinus;
    case kVK_ANSI_KeypadEquals:
        return Keys::KeypadEquals;
    case kVK_ANSI_Keypad0:
        return Keys::Keypad0;
    case kVK_ANSI_Keypad1:
        return Keys::Keypad1;
    case kVK_ANSI_Keypad2:
        return Keys::Keypad2;
    case kVK_ANSI_Keypad3:
        return Keys::Keypad3;
    case kVK_ANSI_Keypad4:
        return Keys::Keypad4;
    case kVK_ANSI_Keypad5:
        return Keys::Keypad5;
    case kVK_ANSI_Keypad6:
        return Keys::Keypad6;
    case kVK_ANSI_Keypad7:
        return Keys::Keypad7;
    case kVK_ANSI_Keypad8:
        return Keys::Keypad8;
    case kVK_ANSI_Keypad9:
        return Keys::Keypad9;
    case kVK_Return:
        return Keys::Return;
    case kVK_Tab:
        return Keys::Tab;
    case kVK_Space:
        return Keys::Space;
    case kVK_Delete:
        return Keys::Backspace;
    case kVK_Escape:
        return Keys::Escape;
    case kVK_Command:
        return Keys::LeftCommand;
    case kVK_Shift:
        return Keys::LeftShift;
    case kVK_CapsLock:
        return Keys::CapsLock;
    case kVK_Option:
        return Keys::LeftAlt;
    case kVK_Control:
        return Keys::LeftControl;
    case kVK_RightShift:
        return Keys::RightShift;
    case kVK_RightOption:
        return Keys::RightAlt;
    case kVK_RightControl:
        return Keys::RightControl;
    case kVK_Function:
        return Keys::Fn;
    case kVK_F17:
        return Keys::F17;
    case kVK_VolumeUp:
        return Keys::VolumeUp;
    case kVK_VolumeDown:
        return Keys::VolumeDown;
    case kVK_Mute:
        return Keys::Mute;
    case kVK_F18:
        return Keys::F18;
    case kVK_F19:
        return Keys::F19;
    case kVK_F20:
        return Keys::F20;
    case kVK_F5:
        return Keys::F5;
    case kVK_F6:
        return Keys::F6;
    case kVK_F7:
        return Keys::F7;
    case kVK_F3:
        return Keys::F3;
    case kVK_F8:
        return Keys::F8;
    case kVK_F9:
        return Keys::F9;
    case kVK_F11:
        return Keys::F11;
    case kVK_F13:
        return Keys::F13;
    case kVK_F16:
        return Keys::F16;
    case kVK_F14:
        return Keys::F14;
    case kVK_F10:
        return Keys::F10;
    case kVK_F12:
        return Keys::F12;
    case kVK_F15:
        return Keys::F15;
    case kVK_Help:
        return Keys::Help;
    case kVK_Home:
        return Keys::Home;
    case kVK_PageUp:
        return Keys::PageUp;
    case kVK_ForwardDelete:
        return Keys::Delete;
    case kVK_F4:
        return Keys::F4;
    case kVK_End:
        return Keys::End;
    case kVK_F2:
        return Keys::F2;
    case kVK_PageDown:
        return Keys::PageDown;
    case kVK_F1:
        return Keys::F1;
    case kVK_LeftArrow:
        return Keys::Left;
    case kVK_RightArrow:
        return Keys::Right;
    case kVK_DownArrow:
        return Keys::Down;
    case kVK_UpArrow:
        return Keys::Up;
    case 0x36:
        return Keys::RightCommand;
    default:
        return Keys::Unknown;
    }
}

@interface GLView : NSOpenGLView <NSWindowDelegate, NSApplicationDelegate>
{
    OSXWindow* window_;
}

- (instancetype)initWithFrame:(CGRect)bounds window:(OSXWindow*)window;
@end

@implementation GLView

- (instancetype)initWithFrame:(CGRect)bounds window:(OSXWindow*)window {
    if (self = [super initWithFrame:bounds]) {
        window_ = window;
        
        NSOpenGLPixelFormatAttribute attrs[] = {
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFADepthSize, 24,
            0
        };
        
        NSOpenGLPixelFormat *pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
        
        if (!pf) {
            Log::W("failed to init the specified pixel format, use default value");
            return self;
        }
        
        self.pixelFormat = pf;
        self.openGLContext = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
    }
    return self;
}

- (void)prepareOpenGL {
    [super prepareOpenGL];
    
    [self.openGLContext makeCurrentContext];
    [self setWantsBestResolutionOpenGLSurface:YES];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    
    // vsync
    [self.openGLContext setValues:(GLint[]){0} forParameter:NSOpenGLCPSwapInterval];
    
    window_->Prepare(*window_);
    
    NSTimer *renderTimer = [NSTimer timerWithTimeInterval:0.0001
                                          target:self
                                        selector:@selector(redraw:)
                                        userInfo:nil
                                         repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:renderTimer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:renderTimer forMode:NSEventTrackingRunLoopMode];
}

- (void)redraw:(id)sender {
    self.needsDisplay = YES;
}

- (void)reshape {
    [super reshape];
    
    NSRect rect = [self convertRectToBacking:[self bounds]];
    
    Viewport(0, 0, rect.size.width, rect.size.height);
    NSLog(@"viewport %.1f x %.1f", rect.size.width, rect.size.height);

    MatrixMode(PROJECTION_MATRIX);
    LoadIdentity();
    Ortho(0, rect.size.width, rect.size.height, 0, -1, 1);
    MatrixMode(MODELVIEW_MATRIX);
    LoadIdentity();
}

- (void)drawRect:(NSRect)rect {
    [self.openGLContext makeCurrentContext];
    PushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    
    window_->Draw(*window_);
    
    PopMatrix();
    [self.openGLContext flushBuffer];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (BOOL)windowShouldClose:(id)sender {
    return window_->OnClosing();
}

- (void)windowWillClose:(NSNotification*)notification {
    [[NSApplication sharedApplication] stop:self];
}

KeyEvent getKeyEvent(NSEvent* event) {
    KeyEvent keyEvent;
    keyEvent.keyCode = event.keyCode;
    keyEvent.key = getKey(event.keyCode);

    NSEventModifierFlags modifiers = event.modifierFlags;
    keyEvent.modifiers.control = CHECK_MASK(modifiers, NSControlKeyMask) ? 1 : 0;
    keyEvent.modifiers.shift = CHECK_MASK(modifiers, NSShiftKeyMask) ? 1 : 0;
    keyEvent.modifiers.alt = CHECK_MASK(modifiers, NSAlternateKeyMask) ? 1 : 0;
    keyEvent.modifiers.command = CHECK_MASK(modifiers, NSCommandKeyMask) ? 1 : 0;

    return keyEvent;
}

MouseEvent getMouseEvent(NSView* view, NSEvent* event, MouseButton button, MouseAction action) {
    MouseEvent mouseEvent;
    NSPoint location = [event locationInWindow];
    mouseEvent.x = location.x;
    mouseEvent.y = view.bounds.size.height - 1 - location.y;
    mouseEvent.button = button;
    mouseEvent.action = action;
    mouseEvent.pressedButtons = [NSEvent pressedMouseButtons];
    return mouseEvent;
}

- (void)keyEventInternal:(KeyEvent)keyEvent {
    window_->OnKeyEvent(keyEvent);
    if (keyEvent.action == KeyAction::Char) {
        NSLog(@"Char '%@'", [NSString stringWithUTF8String:keyEvent.keyChar.c_str()]);
        //printf("Char '%s'\n", keyEvent.keyChar.c_str());
    } else {
        NSLog(@"%s %s %s%s%s%s", 
            keyEvent.getKeyName().c_str(), 
            keyEvent.action == KeyAction::Down ? "Down" :
                keyEvent.action == KeyAction::Up ? "Up" : "Char", 
            keyEvent.hasControl() ? "Ctrl " : "",
            keyEvent.hasShift() ? "Shift " : "",
            keyEvent.hasCommand() ? "Command " : "",
            keyEvent.hasAlt() ? "Alt " : "");
    }
}

- (void)mouseEventInternal:(MouseEvent)mouseEvent {
    window_->OnMouseEvent(mouseEvent);
    NSLog(@"%s%s (%d, %d) %@",
        mouseEvent.button == MouseButton::Left ? "Left "
            : mouseEvent.button == MouseButton::Right ? "Right "
            : mouseEvent.button == MouseButton::Middle ? "Middle " : "",
        mouseEvent.action == MouseAction::Down ? "Down"
            : mouseEvent.action == MouseAction::Up ? "Up"
            : mouseEvent.action == MouseAction::Wheel ? "Wheel" : "Move",
        mouseEvent.x, 
        mouseEvent.y,
        mouseEvent.action == MouseAction::Wheel ? [NSString stringWithFormat:@"%.1f", mouseEvent.wheel] : @"");
}

- (void)keyDown:(NSEvent *)event {
    if (![event isARepeat]) {
        KeyEvent keyEvent = getKeyEvent(event);
        keyEvent.action = KeyAction::Down;
        [self keyEventInternal:keyEvent];
    }
    
    KeyEvent keyEvent = getKeyEvent(event);
    keyEvent.keyChar = event.characters.UTF8String;
    keyEvent.action = KeyAction::Char;
    [self keyEventInternal:keyEvent];
}

- (void)keyUp:(NSEvent *)event {
    KeyEvent keyEvent = getKeyEvent(event);
    keyEvent.keyChar = event.characters.UTF8String;
    keyEvent.action = KeyAction::Up;
    [self keyEventInternal:keyEvent];
}

- (void)flagsChanged:(NSEvent *)event {
    KeyEvent keyEvent = getKeyEvent(event);
    NSEventModifierFlags modifiers = event.modifierFlags;
    switch (keyEvent.key) {
    case Keys::CapsLock:
        keyEvent.action = CHECK_MASK(modifiers, NX_ALPHASHIFTMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::LeftShift:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICELSHIFTKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::LeftControl:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICELCTLKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::LeftAlt:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICELALTKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::LeftCommand:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICELCMDKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::RightShift:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICERSHIFTKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::RightControl:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICERCTLKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::RightAlt:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICERALTKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::RightCommand:
        keyEvent.action = CHECK_MASK(modifiers, NX_DEVICERCMDKEYMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    case Keys::Fn:
        keyEvent.action = CHECK_MASK(modifiers, NX_SECONDARYFNMASK) ? KeyAction::Down : KeyAction::Up;
        break;
    default:
        NSLog(@"warning: unknown modifier key, the action is improbable");
    }
    [self keyEventInternal:keyEvent];
}

- (void)mouseDown:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Left, MouseAction::Down)];
}

- (void)mouseUp:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Left, MouseAction::Up)];
}

- (void)mouseDragged:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Left, MouseAction::Move)];
}

- (void)rightMouseDown:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Right, MouseAction::Down)];
}

- (void)rightMouseUp:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Right, MouseAction::Up)];
}

- (void)rightMouseDragged:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Right, MouseAction::Move)];
}

- (void)otherMouseDown:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Middle, MouseAction::Down)];
}

- (void)otherMouseUp:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Middle, MouseAction::Up)];
}

- (void)otherMouseDragged:(NSEvent *)event {
    [self mouseEventInternal:getMouseEvent(self, event, MouseButton::Middle, MouseAction::Move)];
}

- (void)mouseMoved:(NSEvent *)event {
    MouseEvent mouseEvent = getMouseEvent(self, event, MouseButton::None, MouseAction::Move);
    if (CGRectContainsPoint(self.bounds, CGPointMake(mouseEvent.x, mouseEvent.y))) {
        [self mouseEventInternal:mouseEvent];
    }
}

- (void)mouseEntered:(NSEvent *)event {
    NSPoint location = [NSEvent mouseLocation];
    NSLog(@"mouseEntered (%.1f, %.1f) %ld %lu", location.x, location.y, event.buttonNumber, [NSEvent pressedMouseButtons]);
}

- (void)mouseExited:(NSEvent *)event {
    NSPoint location = [NSEvent mouseLocation];
    NSLog(@"mouseExited (%.1f, %.1f) %ld %lu", location.x, location.y, event.buttonNumber, [NSEvent pressedMouseButtons]);
}

- (void)scrollWheel:(NSEvent *)event {
    MouseEvent mouseEvent = getMouseEvent(self, event, MouseButton::None, MouseAction::Wheel);
    mouseEvent.wheel = event.deltaY;
    [self mouseEventInternal:mouseEvent];
}

@end

namespace unnamed {

struct OSXWindowContext {
    NSWindow* window = nullptr;
};

OSXWindow::OSXWindow(WindowOptions options) : Window(options) {
    context_ = new OSXWindowContext();
}

OSXWindow::~OSXWindow() {
    if (context_) {
        delete context_;
    }
}

bool OSXWindow::Create() {
    @autoreleasepool {
        NSRect rect = NSMakeRect(0, 0, options_.width, options_.height);
        GLView *view = [[GLView alloc] initWithFrame:rect window:this];
        if (!view) {
            return false;
        }

        NSWindow *window = [[NSWindow alloc]
                      initWithContentRect:rect
                      styleMask:NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask
                      backing:NSBackingStoreBuffered
                      defer:NO];
        
        if (options_.fullscreen) {
            [context_->window toggleFullScreen:nil];
        }
        
        window.acceptsMouseMovedEvents = YES;
        window.contentView = view;
        window.title = [NSString stringWithUTF8String:options_.title.c_str()];
        window.delegate = view;
        [window center];
        [window makeKeyAndOrderFront:nil];
        [NSApplication sharedApplication].delegate = view;
        context_->window = window;
    }

    return true;
}

void OSXWindow::Run() {
    [[NSApplication sharedApplication] run];
    OnClosed();
}

void OSXWindow::Close() {
    [context_->window close];
}

int OSXWindow::GetWidth() {
    return context_->window.contentView.frame.size.width*2;
}

int OSXWindow::GetHeight() {
    return context_->window.contentView.frame.size.height*2;
}

void OSXWindow::SetTitle(const std::string& title) {
    context_->window.title = [NSString stringWithUTF8String:title.c_str()];
}

}

#endif
