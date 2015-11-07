#pragma once

#include "Base/Event.hpp"

#include <string>

namespace unnamed {

struct WindowOptions {
	std::string title;
	int width;
	int height;
	bool fullscreen;
	bool vsync;
};

enum class MouseButton {
	None = 0,
	Left = 1,
	Right = 2,
	Middle = 4
};

enum class MouseAction {
	Move,
	Down,
	Up,
    Wheel
};

enum class KeyAction {
	Down,
	Up,
    Char
};

enum class Keys {
    Unknown,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Grave,          // `
    Minus,          // -
    Equal,          // =
    LeftBracket,    // [
    RightBracket,   // ]
    Backslash,      // '\'
    Semicolon,      // ;
    Quote,          // '
    Comma,          // ,
    Period,         // .
    Slash,          // /
    Keypad0,
    Keypad1,
    Keypad2,
    Keypad3,
    Keypad4,
    Keypad5,
    Keypad6,
    Keypad7,
    Keypad8,
    Keypad9,
    KeypadDecimal,  // .
    KeypadPlus,     // +
    KeypadMinus,    // -
    KeypadMultiply, // *
    KeypadDivide,   // /
    KeypadEquals,   // =
    KeypadEnter,
    KeypadClear,
    Return,
    Backspace,
    Delete,
    Escape,
    Tab,
    CapsLock,
    LeftShift,
    LeftControl,
    LeftAlt,
    LeftCommand,
    Space,
    Left,
    Right,
    Up,
    Down,
    RightCommand,
    RightAlt,
    RightControl,
    RightShift,
    Home,
    End,
    PageUp,
    PageDown,
    Pause,
    Select,
    PrintScreen,
    Help,
    Insert,
    VolumeUp,
    VolumeDown,
    Mute,
    Fn,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20
};

struct MouseEvent {
	int x;
	int y;
    float wheel;
	MouseButton button;
	MouseAction action;
    int pressedButtons;
};

struct KeyEvent {
    int keyCode;
	std::string keyChar;
    Keys key;
	union {
		int modifiers;
		struct {
			int control:1;
			int shift:1;
			int alt:1;
			int command:1;
		};
	} modifiers;
	KeyAction action;

    std::string getKeyName();
    bool hasControl() { return modifiers.control; }
    bool hasShift() { return modifiers.shift; }
    bool hasAlt() { return modifiers.alt; }
    bool hasCommand() { return modifiers.command; }
    bool isControl() { return key == Keys::LeftControl || key == Keys::RightControl; }
    bool isShift() { return key == Keys::LeftShift || key == Keys::RightShift; }
    bool isAlt() { return key == Keys::LeftAlt || key == Keys::RightAlt; }
    bool isCommand() { return key == Keys::LeftCommand || key == Keys::RightCommand; }
};

class Window {
public:
    me::Event<Window> Draw;
    
	Window(WindowOptions options) { options_ = options; }
	virtual bool Create() = 0;
	virtual void Run() = 0;
	virtual void Close() = 0;
	virtual bool OnClosing() { return true; }
	virtual void OnClosed() {}
	virtual void OnMouseEvent(const MouseEvent& event) {}
	virtual void OnKeyEvent(const KeyEvent& event) {}
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

protected:
	WindowOptions options_;
};

}
