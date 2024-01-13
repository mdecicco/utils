#include <utils/Window.h>
#include <utils/Array.hpp>
#include <utils/Input.h>
#include <utils/Array.hpp>

#ifdef _WIN32
#include <Windows.h>
#include <Windowsx.h>
#else
#endif

namespace utils {
    bool isKeyCodeValid(u32 code) {
        switch (code) {
            case KEY_0:
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
            case KEY_A:
            case KEY_B:
            case KEY_C:
            case KEY_D:
            case KEY_E:
            case KEY_F:
            case KEY_G:
            case KEY_H:
            case KEY_I:
            case KEY_J:
            case KEY_K:
            case KEY_L:
            case KEY_M:
            case KEY_N:
            case KEY_O:
            case KEY_P:
            case KEY_Q:
            case KEY_R:
            case KEY_S:
            case KEY_T:
            case KEY_U:
            case KEY_V:
            case KEY_W:
            case KEY_X:
            case KEY_Y:
            case KEY_Z:
            case KEY_SINGLE_QUOTE:
            case KEY_BACKSLASH:
            case KEY_COMMA:
            case KEY_EQUAL:
            case KEY_BACKTICK:
            case KEY_LEFT_BRACKET:
            case KEY_MINUS:
            case KEY_PERIOD:
            case KEY_RIGHT_BRACKET:
            case KEY_SEMICOLON:
            case KEY_SLASH:
            case KEY_BACKSPACE:
            case KEY_DELETE:
            case KEY_END:
            case KEY_ENTER:
            case KEY_ESCAPE:
            case KEY_HOME:
            case KEY_INSERT:
            case KEY_MENU:
            case KEY_PAGE_DOWN:
            case KEY_PAGE_UP:
            case KEY_PAUSE:
            case KEY_SPACE:
            case KEY_TAB:
            case KEY_CAP_LOCK:
            case KEY_NUM_LOCK:
            case KEY_SCROLL_LOCK:
            case KEY_F1:
            case KEY_F2:
            case KEY_F3:
            case KEY_F4:
            case KEY_F5:
            case KEY_F6:
            case KEY_F7:
            case KEY_F8:
            case KEY_F9:
            case KEY_F10:
            case KEY_F11:
            case KEY_F12:
            case KEY_F13:
            case KEY_F14:
            case KEY_F15:
            case KEY_F16:
            case KEY_F17:
            case KEY_F18:
            case KEY_F19:
            case KEY_F20:
            case KEY_F21:
            case KEY_F22:
            case KEY_F23:
            case KEY_F24:
            case KEY_LEFT_ALT:
            case KEY_LEFT_CONTROL:
            case KEY_LEFT_SHIFT:
            case KEY_LEFT_SUPER:
            case KEY_PRINT_SCREEN:
            case KEY_RIGHT_ALT:
            case KEY_RIGHT_CONTROL:
            case KEY_RIGHT_SHIFT:
            case KEY_RIGHT_SUPER:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_UP:
            case KEY_NUMPAD_0:
            case KEY_NUMPAD_1:
            case KEY_NUMPAD_2:
            case KEY_NUMPAD_3:
            case KEY_NUMPAD_4:
            case KEY_NUMPAD_5:
            case KEY_NUMPAD_6:
            case KEY_NUMPAD_7:
            case KEY_NUMPAD_8:
            case KEY_NUMPAD_9:
            case KEY_NUMPAD_ADD:
            case KEY_NUMPAD_DECIMAL:
            case KEY_NUMPAD_DIVIDE:
            case KEY_NUMPAD_ENTER:
            case KEY_NUMPAD_EQUAL:
            case KEY_NUMPAD_MULTIPLY:
            case KEY_NUMPAD_SUBTRACT: return true;
            default: return false;
        }
    }

    #ifdef _WIN32
    LRESULT CALLBACK __windowProc(HWND win, UINT uMsg, WPARAM wParam, LPARAM lParam);
    BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
    #else
    #endif

    Window::Window() {
        m_width = m_height = UINT32_MAX;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = nullptr;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(const String& title) {
        m_title = title;
        m_width = m_height = UINT32_MAX;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = nullptr;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(u32 width, u32 height) {
        m_width = width;
        m_height = height;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = nullptr;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(const String& title, u32 width, u32 height) {
        m_title = title;
        m_width = width;
        m_height = height;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = nullptr;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(Window* parent) {
        m_width = m_height = UINT32_MAX;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = parent;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(Window* parent, const String& title) {
        m_title = title;
        m_width = m_height = UINT32_MAX;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = parent;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(Window* parent, u32 width, u32 height) {
        m_width = width;
        m_height = height;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = parent;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::Window(Window* parent, const String& title, u32 width, u32 height) {
        m_title = title;
        m_width = width;
        m_height = height;
        m_posX = m_posY = 0;
        m_isOpen = false;
        m_borderless = false;
        m_parent = parent;

        #ifdef _WIN32
        m_windowHandle = nullptr;
        #else
        #endif
    }

    Window::~Window() {
        #ifdef _WIN32
        
        if (m_windowHandle) {
            destroyWindowHandle_win32();
        }

        #else
        #endif
    }

    bool Window::isValid() const {
        #ifdef _WIN32
        return m_windowHandle != nullptr;
        #else
        #endif

        return false;
    }

    bool Window::setTitle(const String& title) {
        #ifdef _WIN32
        
        if (!m_windowHandle) {
            m_title = title;
            return true;
        }

        if (SetWindowText(m_windowHandle, title.c_str()) == TRUE) {
            m_title = title;
            return true;
        }

        #else
        #endif

        return false;
    }

    const String& Window::getTitle() const {
        return m_title;
    }

    bool Window::setSize(u32 width, u32 height) {
        #ifdef _WIN32

        if (!m_windowHandle) {
            m_width = width;
            m_height = height;
            return true;
        }
        
        if (SetWindowPos(m_windowHandle, nullptr, m_posX, m_posY, width, height, SWP_NOMOVE) == TRUE) {
            m_width = width;
            m_height = height;
            return true;
        }

        #else
        #endif

        return false;
    }

    void Window::getSize(u32* width, u32* height) {
        if (width) *width = m_width;
        if (height) *height = m_height;
    }

    bool Window::setPosition(i32 x, i32 y) {
        #ifdef _WIN32

        if (!m_windowHandle) {
            m_posX = x;
            m_posY = y;
            return true;
        }
        
        if (SetWindowPos(m_windowHandle, nullptr, x, y, m_width, m_height, SWP_NOSIZE) == TRUE) {
            m_posX = x;
            m_posY = y;
            return true;
        }

        #else
        #endif

        return false;
    }

    void Window::getPosition(i32* x, i32* y) {
        if (x) *x = m_posX;
        if (y) *y = m_posY;
    }

    bool Window::setOpen(bool doOpen) {
        #ifdef _WIN32

        if (doOpen == m_isOpen) return true;

        if (!doOpen) {
            if (!m_windowHandle) return false;
            ShowWindow(m_windowHandle, SW_HIDE);
            m_isOpen = false;
            return true;
        }

        if (m_parent && !m_parent->m_windowHandle) return false;

        if (m_windowHandle) {
            ShowWindow(m_windowHandle, SW_SHOWNORMAL);
            m_isOpen = true;
            return true;
        }

        if (!createWindowHandle_win32()) return false;

        m_isOpen = true;
        return true;

        #else
        #endif

        return false;
    }

    bool Window::isOpen() const {
        return m_isOpen;
    }
    
    void Window::setBorderEnabled(bool enabled) {
        #ifdef _WIN32

        if (!m_windowHandle || enabled != m_borderless) {
            m_borderless = !enabled;
            return;
        }

        if (!enabled) {
            LONG lStyle = GetWindowLong(m_windowHandle, GWL_STYLE);
            lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
            SetWindowLong(m_windowHandle, GWL_STYLE, lStyle);

            LONG lExStyle = GetWindowLong(m_windowHandle, GWL_EXSTYLE);
            lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
            SetWindowLong(m_windowHandle, GWL_EXSTYLE, lExStyle);

            bool result = SetWindowPos(
                m_windowHandle,
                NULL,
                0,0,0,0,
                SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER
            );

            if (result) m_borderless = true;
        } else {
            LONG lStyle = GetWindowLong(m_windowHandle, GWL_STYLE);
            lStyle |= WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;
            SetWindowLong(m_windowHandle, GWL_STYLE, lStyle);

            LONG lExStyle = GetWindowLong(m_windowHandle, GWL_EXSTYLE);
            lExStyle |= WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE;
            SetWindowLong(m_windowHandle, GWL_EXSTYLE, lExStyle);

            bool result = SetWindowPos(
                m_windowHandle,
                NULL,
                0,0,0,0,
                SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER
            );

            if (result) m_borderless = false;
        }

        #else
        #endif
    }

    void Window::subscribe(IInputHandler* inputHandler) {
        IInputHandler* existing = m_listeners.find([inputHandler](IInputHandler* h) {
            return h == inputHandler;
        });

        if (existing) return;

        m_listeners.push(inputHandler);
    }

    void Window::unsubscribe(IInputHandler* inputHandler) {
        i64 idx = m_listeners.findIndex([inputHandler](IInputHandler* h) {
            return h == inputHandler;
        });

        if (idx == -1) return;

        m_listeners.remove(u32(idx));
    }

    bool Window::pollEvents() {
        #ifdef _WIN32
        if (!m_windowHandle) return false;

        u32 count = 0;
        MSG message;
        while (PeekMessage(&message, m_windowHandle, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
            count++;
        }

        return count > 0;

        #else
        #endif

        return false;
    }

    Array<MonitorInfo> Window::GetMonitors() {
        #ifdef _WIN32
            HMONITOR primary = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
            Array<MonitorInfo> out;
            EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, (LPARAM)&out);

            for(u32 i = 0;i < out.size();i++) {
                if (out[i].handle == primary) {
                    out[i].isPrimary = true;
                    break;
                }
            }

            return out;
        #else
        #endif

        return Array<MonitorInfo>();
    }

    void Window::onResize() {
        #ifdef _WIN32
            RECT rect;
            if (GetWindowRect(m_windowHandle, &rect)) {
                m_width = rect.right - rect.left;
                m_height = rect.bottom - rect.top;
                m_posX = rect.left;
                m_posY = rect.top;

                m_listeners.each([this](IInputHandler* h) {
                    h->onWindowResize(this, m_width, m_height);
                });
            }
        #else
        #endif
    }

    void Window::onMove() {
        #ifdef _WIN32
            RECT rect;
            if (GetWindowRect(m_windowHandle, &rect)) {
                m_width = rect.right - rect.left;
                m_height = rect.bottom - rect.top;
                m_posX = rect.left;
                m_posY = rect.top;

                m_listeners.each([this](IInputHandler* h) {
                    h->onWindowMove(this, m_posX, m_posY);
                });
            }
        #else
        #endif
    }
    
    void Window::onClose() {
        setOpen(false);
    }
    
    void Window::onDestroy() {
        #ifdef _WIN32
            m_windowHandle = nullptr;
        #else
        #endif
        m_isOpen = false;
    }

    #ifdef _WIN32

    HWND Window::getHandle() {
        return m_windowHandle;
    }
    
    bool Window::createWindowHandle_win32() {
        SetProcessDPIAware();

        String className = String::Format("WinUtil_%d", rand());
        WNDCLASSEX wnd;
        wnd.hInstance = GetModuleHandle(nullptr);
        wnd.lpszClassName = className.c_str();
        wnd.lpfnWndProc = __windowProc;
        wnd.style = CS_DBLCLKS;
        wnd.cbSize = sizeof(WNDCLASSEX);
        wnd.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wnd.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wnd.lpszMenuName = nullptr;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = sizeof(Window*);
        wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

        if (!RegisterClassEx(&wnd)) return false;

        u32 styleFlags;
        if (m_borderless) styleFlags = WS_OVERLAPPED;
        else styleFlags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

        m_windowHandle = CreateWindowEx(
            0,
            className.c_str(),
            m_title.c_str(),
            styleFlags,
            m_posX == UINT32_MAX ? CW_USEDEFAULT : m_posX,
            m_posY == UINT32_MAX ? CW_USEDEFAULT : m_posY,
            m_width == UINT32_MAX ? 800 : m_width,
            m_height == UINT32_MAX ? 600 : m_height,
            m_parent ? m_parent->m_windowHandle : HWND_DESKTOP,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        if (!m_windowHandle) return false;
        SetWindowLongPtr(m_windowHandle, 0, (LONG_PTR)this);
        ShowWindow(m_windowHandle, SW_SHOWNORMAL);

        // Don't ask me why CreateWindowEx won't just create the window with the correct style from the beginning...
        if (m_borderless) {
            m_borderless = false;
            setBorderEnabled(false);
        }

        RECT rect;
        if (GetWindowRect(m_windowHandle, &rect)) {
            m_width = rect.right - rect.left;
            m_height = rect.bottom - rect.top;
            m_posX = rect.left;
            m_posY = rect.top;
        }

        return true;
    }

    bool Window::destroyWindowHandle_win32() {
        if (!m_windowHandle) return true;
        return DestroyWindow(m_windowHandle) == TRUE;
    }

    LRESULT CALLBACK __windowProc(HWND win, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        Window* self = (Window*)GetWindowLongPtr(win, 0);

        switch (uMsg) {
            case WM_CLOSE: { self->onClose(); return 0; }
            case WM_DESTROY: { self->onDestroy(); break; }
            case WM_SIZE: { self->onResize(); break; }
            case WM_MOVE: { self->onMove(); break; }
            case WM_KEYDOWN: {
                KeyboardKey code = KeyboardKey(HIWORD(lParam) & (KF_EXTENDED | 0xff));
                if (code == KEY_NONE) code = KeyboardKey(MapVirtualKeyW(u32(wParam), MAPVK_VK_TO_VSC));
                if (!isKeyCodeValid(code)) break;
                
                self->m_listeners.each([code](IInputHandler* h) {
                    h->onKeyDown(code);
                });

                break;
            }
            case WM_KEYUP: {
                KeyboardKey code = KeyboardKey(HIWORD(lParam) & (KF_EXTENDED | 0xff));
                if (code == KEY_NONE) code = KeyboardKey(MapVirtualKeyW(u32(wParam), MAPVK_VK_TO_VSC));
                if (!isKeyCodeValid(code)) break;

                self->m_listeners.each([code](IInputHandler* h) {
                    h->onKeyUp(code);
                });

                break;
            }
            case WM_CHAR: {
                u8 ch = u8(wParam);
                self->m_listeners.each([ch](IInputHandler* h) {
                    h->onChar(u8(ch));
                });

                break;
            }
            case WM_MOUSEMOVE: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseMove(
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    );
                });

                break;
            }
            case WM_MOUSEWHEEL: {
                i16 x = HIWORD(wParam);
                f32 d = x / f32(WHEEL_DELTA);
                self->m_listeners.each([d](IInputHandler* h) {
                    h->onScroll(d);
                });

                break;
            }
            case WM_LBUTTONDOWN: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseDown(LEFT_BUTTON);
                });

                break;
            }
            case WM_LBUTTONUP: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseUp(LEFT_BUTTON);
                });

                break;
            }
            case WM_MBUTTONDOWN: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseDown(MIDDLE_BUTTON);
                });

                break;
            }
            case WM_MBUTTONUP: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseUp(MIDDLE_BUTTON);
                });

                break;
            }
            case WM_RBUTTONDOWN: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseDown(RIGHT_BUTTON);
                });

                break;
            }
            case WM_RBUTTONUP: {
                self->m_listeners.each([lParam](IInputHandler* h) {
                    h->onMouseUp(RIGHT_BUTTON);
                });

                break;
            }
        }

        return DefWindowProc(win, uMsg, wParam, lParam);
    }
    
    BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
        Array<MonitorInfo>& arr = *(Array<MonitorInfo>*)dwData;

        MONITORINFOEX minfo;
        minfo.cbSize = sizeof(MONITORINFOEX);
        
        if (!GetMonitorInfo(hMonitor, &minfo)) {
            return TRUE;
        }
        
        arr.push({});
        MonitorInfo& mi = arr.last();

        DEVMODE devmode = {};
        devmode.dmSize = sizeof(DEVMODE);
        EnumDisplaySettings(minfo.szDevice, ENUM_CURRENT_SETTINGS, &devmode);

        mi.virtualDimensions = vec2ui(
            minfo.rcMonitor.right - minfo.rcMonitor.left,
            minfo.rcMonitor.bottom - minfo.rcMonitor.top
        );
        mi.actualDimensions = vec2ui(
            devmode.dmPelsWidth,
            devmode.dmPelsHeight
        );
        mi.position = vec2i(
            minfo.rcMonitor.left,
            minfo.rcMonitor.top
        );
        mi.bitsPerPixel = devmode.dmBitsPerPel;
        mi.refreshRate = devmode.dmDisplayFrequency;
        mi.handle = hMonitor;

        return TRUE;
    }
    #else
    #endif
};