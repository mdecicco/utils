#include <utils/Input.h>

namespace utils {
    IInputHandler::IInputHandler() {}
    IInputHandler::~IInputHandler() {}
    void IInputHandler::onKeyDown(KeyboardKey key) {}
    void IInputHandler::onKeyUp(KeyboardKey key) {}
    void IInputHandler::onChar(u8 code) {}
    void IInputHandler::onMouseDown(MouseButton buttonIdx) {}
    void IInputHandler::onMouseUp(MouseButton buttonIdx) {}
    void IInputHandler::onMouseMove(i32 x, i32 y) {}
    void IInputHandler::onScroll(f32 delta) {}
    void IInputHandler::onWindowResize(Window* win, u32 width, u32 height) {}
    void IInputHandler::onWindowMove(Window* win, i32 x, i32 y) {}
    void IInputHandler::onGamepadConnected(i32 id) {}
    void IInputHandler::onGamepadDisconnected(i32 id) {}
    void IInputHandler::onGamepadAxisChanged(i32 id, u8 axisIdx, f32 value) {}
    void IInputHandler::onGamepadButtonDown(i32 gamepadId, u8 buttonIdx) {}
    void IInputHandler::onGamepadButtonUp(i32 gamepadId, u8 buttonIdx) {}
};