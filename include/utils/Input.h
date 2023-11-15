#pragma once
#include <utils/Types.h>

namespace utils {
    enum MouseButton {
        LEFT_BUTTON,
        MIDDLE_BUTTON,
        RIGHT_BUTTON
    };

    class IInputHandler {
        public:
            IInputHandler();
            virtual ~IInputHandler();

            virtual void onKeyDown(u8 code);
            virtual void onKeyUp(u8 code);
            virtual void onChar(u8 code);
            virtual void onMouseDown(MouseButton buttonIdx);
            virtual void onMouseUp(MouseButton buttonIdx);
            virtual void onMouseMove(i32 x, i32 y);
            virtual void onScroll(i32 delta);

            // todo
            virtual void onGamepadConnected(i32 id);
            virtual void onGamepadDisconnected(i32 id);
            virtual void onGamepadAxisChanged(i32 id, u8 axisIdx, f32 value);
            virtual void onGamepadButtonDown(i32 gamepadId, u8 buttonIdx);
            virtual void onGamepadButtonUp(i32 gamepadId, u8 buttonIdx);
    };
};