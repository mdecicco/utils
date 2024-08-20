#pragma once
#include <utils/Types.h>

namespace utils {
    class Window;
    
    enum MouseButton {
        LEFT_BUTTON,
        MIDDLE_BUTTON,
        RIGHT_BUTTON
    };

    enum KeyboardKey {
        KEY_NONE            = 0,
        KEY_0               = 0x00B,
        KEY_1               = 0x002,
        KEY_2               = 0x003,
        KEY_3               = 0x004,
        KEY_4               = 0x005,
        KEY_5               = 0x006,
        KEY_6               = 0x007,
        KEY_7               = 0x008,
        KEY_8               = 0x009,
        KEY_9               = 0x00A,
        KEY_A               = 0x01E,
        KEY_B               = 0x030,
        KEY_C               = 0x02E,
        KEY_D               = 0x020,
        KEY_E               = 0x012,
        KEY_F               = 0x021,
        KEY_G               = 0x022,
        KEY_H               = 0x023,
        KEY_I               = 0x017,
        KEY_J               = 0x024,
        KEY_K               = 0x025,
        KEY_L               = 0x026,
        KEY_M               = 0x032,
        KEY_N               = 0x031,
        KEY_O               = 0x018,
        KEY_P               = 0x019,
        KEY_Q               = 0x010,
        KEY_R               = 0x013,
        KEY_S               = 0x01F,
        KEY_T               = 0x014,
        KEY_U               = 0x016,
        KEY_V               = 0x02F,
        KEY_W               = 0x011,
        KEY_X               = 0x02D,
        KEY_Y               = 0x015,
        KEY_Z               = 0x02C,
        KEY_SINGLE_QUOTE    = 0x028,
        KEY_BACKSLASH       = 0x02B,
        KEY_COMMA           = 0x033,
        KEY_EQUAL           = 0x00D,
        KEY_BACKTICK        = 0x029,
        KEY_LEFT_BRACKET    = 0x01A,
        KEY_MINUS           = 0x00C,
        KEY_PERIOD          = 0x034,
        KEY_RIGHT_BRACKET   = 0x01B,
        KEY_SEMICOLON       = 0x027,
        KEY_SLASH           = 0x035,
        KEY_BACKSPACE       = 0x00E,
        KEY_DELETE          = 0x153,
        KEY_END             = 0x14F,
        KEY_ENTER           = 0x01C,
        KEY_ESCAPE          = 0x001,
        KEY_GRAVE_ACCENT    = 0x0C0,
        KEY_HOME            = 0x147,
        KEY_INSERT          = 0x152,
        KEY_MENU            = 0x15D,
        KEY_PAGE_DOWN       = 0x151,
        KEY_PAGE_UP         = 0x149,
        KEY_PAUSE           = 0x045,
        KEY_SPACE           = 0x039,
        KEY_TAB             = 0x00F,
        KEY_CAP_LOCK        = 0x03A,
        KEY_NUM_LOCK        = 0x145,
        KEY_SCROLL_LOCK     = 0x046,
        KEY_F1              = 0x03B,
        KEY_F2              = 0x03C,
        KEY_F3              = 0x03D,
        KEY_F4              = 0x03E,
        KEY_F5              = 0x03F,
        KEY_F6              = 0x040,
        KEY_F7              = 0x041,
        KEY_F8              = 0x042,
        KEY_F9              = 0x043,
        KEY_F10             = 0x044,
        KEY_F11             = 0x057,
        KEY_F12             = 0x058,
        KEY_F13             = 0x064,
        KEY_F14             = 0x065,
        KEY_F15             = 0x066,
        KEY_F16             = 0x067,
        KEY_F17             = 0x068,
        KEY_F18             = 0x069,
        KEY_F19             = 0x06A,
        KEY_F20             = 0x06B,
        KEY_F21             = 0x06C,
        KEY_F22             = 0x06D,
        KEY_F23             = 0x06E,
        KEY_F24             = 0x076,
        KEY_LEFT_ALT        = 0x038,
        KEY_LEFT_CONTROL    = 0x01D,
        KEY_LEFT_SHIFT      = 0x02A,
        KEY_LEFT_SUPER      = 0x15B,
        KEY_PRINT_SCREEN    = 0x137,
        KEY_RIGHT_ALT       = 0x138,
        KEY_RIGHT_CONTROL   = 0x11D,
        KEY_RIGHT_SHIFT     = 0x036,
        KEY_RIGHT_SUPER     = 0x15C,
        KEY_DOWN            = 0x150,
        KEY_LEFT            = 0x14B,
        KEY_RIGHT           = 0x14D,
        KEY_UP              = 0x148,
        KEY_NUMPAD_0        = 0x052,
        KEY_NUMPAD_1        = 0x04F,
        KEY_NUMPAD_2        = 0x050,
        KEY_NUMPAD_3        = 0x051,
        KEY_NUMPAD_4        = 0x04B,
        KEY_NUMPAD_5        = 0x04C,
        KEY_NUMPAD_6        = 0x04D,
        KEY_NUMPAD_7        = 0x047,
        KEY_NUMPAD_8        = 0x048,
        KEY_NUMPAD_9        = 0x049,
        KEY_NUMPAD_ADD      = 0x04E,
        KEY_NUMPAD_DECIMAL  = 0x053,
        KEY_NUMPAD_DIVIDE   = 0x135,
        KEY_NUMPAD_ENTER    = 0x11C,
        KEY_NUMPAD_EQUAL    = 0x059,
        KEY_NUMPAD_MULTIPLY = 0x037,
        KEY_NUMPAD_SUBTRACT = 0x04A
    };

    class IInputHandler {
        public:
            IInputHandler();
            virtual ~IInputHandler();

            virtual void onKeyDown(KeyboardKey key);
            virtual void onKeyUp(KeyboardKey key);
            virtual void onChar(u8 code);
            virtual void onMouseDown(MouseButton buttonIdx);
            virtual void onMouseUp(MouseButton buttonIdx);
            virtual void onMouseMove(i32 x, i32 y);
            virtual void onScroll(f32 delta);
            virtual void onWindowResize(Window* win, u32 width, u32 height);
            virtual void onWindowMove(Window* win, i32 x, i32 y);

            // todo
            virtual void onGamepadConnected(i32 id);
            virtual void onGamepadDisconnected(i32 id);
            virtual void onGamepadAxisChanged(i32 id, u8 axisIdx, f32 value);
            virtual void onGamepadButtonDown(i32 gamepadId, u8 buttonIdx);
            virtual void onGamepadButtonUp(i32 gamepadId, u8 buttonIdx);
    };
};