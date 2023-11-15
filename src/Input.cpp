#include <utils/Input.h>

namespace utils {
    IInputHandler::IInputHandler() {}
    IInputHandler::~IInputHandler() {}
    void IInputHandler::onKeyDown(u8 code) {}
    void IInputHandler::onKeyUp(u8 code) {}
    void IInputHandler::onChar(u8 code) {}
    void IInputHandler::onMouseDown(MouseButton buttonIdx) {}
    void IInputHandler::onMouseUp(MouseButton buttonIdx) {}
    void IInputHandler::onMouseMove(i32 x, i32 y) {}
    void IInputHandler::onScroll(i32 delta) {}
    void IInputHandler::onGamepadConnected(i32 id) {}
    void IInputHandler::onGamepadDisconnected(i32 id) {}
    void IInputHandler::onGamepadAxisChanged(i32 id, u8 axisIdx, f32 value) {}
    void IInputHandler::onGamepadButtonDown(i32 gamepadId, u8 buttonIdx) {}
    void IInputHandler::onGamepadButtonUp(i32 gamepadId, u8 buttonIdx) {}
};