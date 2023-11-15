#include <utils/Window.h>
#include <utils/Array.hpp>
#include <utils/Input.h>

#ifdef _WIN32
#include <Windows.h>
#include <Windowsx.h>
#else
#endif

namespace utils {
    #ifdef _WIN32
    LRESULT CALLBACK __windowProc(HWND win, UINT uMsg, WPARAM wParam, LPARAM lParam);
    #else
    #endif

    Window::Window() {
        m_width = m_height = UINT32_MAX;
        m_posX = m_posY = 0;
        m_isOpen = false;
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
        
        if (SetWindowPos(m_windowHandle, nullptr, m_posX, m_posY, width, height, SWP_NOMOVE) == TRUE) {
            m_width = width;
            m_width = height;
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

        ShowWindow(m_windowHandle, SW_SHOWNORMAL);
        m_isOpen = true;
        return true;

        #else
        #endif

        return false;
    }

    bool Window::isOpen() const {
        return m_isOpen;
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

        m_listeners.remove(idx);
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

    void Window::onResize() {
        RECT rect;
        if (GetWindowRect(m_windowHandle, &rect)) {
            m_width = rect.right - rect.left;
            m_height = rect.bottom - rect.top;
            m_posX = rect.left;
            m_posY = rect.top;
        }
    }

    void Window::onMove() {
        RECT rect;
        if (GetWindowRect(m_windowHandle, &rect)) {
            m_width = rect.right - rect.left;
            m_height = rect.bottom - rect.top;
            m_posX = rect.left;
            m_posY = rect.top;
        }
    }
    
    void Window::onClose() {
        setOpen(false);
    }
    
    void Window::onDestroy() {
        m_windowHandle = nullptr;
        m_isOpen = false;
    }

    #ifdef _WIN32

    HWND Window::getHandle() {
        return m_windowHandle;
    }
    
    bool Window::createWindowHandle_win32() {
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

        m_windowHandle = CreateWindowEx(
            0,
            className.c_str(),
            m_title.c_str(),
            WS_OVERLAPPEDWINDOW,
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
                u8 ch = u8(wParam);
                if (isalpha(ch)) ch = u8(tolower(ch));
                self->m_listeners.each([ch](IInputHandler* h) {
                    h->onKeyDown(ch);
                });

                break;
            }
            case WM_KEYUP: {
                u8 ch = u8(wParam);
                if (isalpha(ch)) ch = u8(tolower(ch));
                self->m_listeners.each([ch](IInputHandler* h) {
                    h->onKeyUp(u8(ch));
                });

                break;
            }
            case WM_CHAR: {
                u8 ch = u8(wParam);
                if (isalpha(ch)) ch = u8(tolower(ch));
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
                self->m_listeners.each([wParam](IInputHandler* h) {
                    h->onScroll(GET_WHEEL_DELTA_WPARAM(wParam));
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
    #else
    #endif
};