#pragma once
#include <utils/Types.h>
#include <utils/String.h>
#include <utils/Math.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#endif

namespace utils {
    class IInputHandler;

    #ifdef _WIN32
    LRESULT CALLBACK __windowProc(HWND win, UINT uMsg, WPARAM wParam, LPARAM lParam);
    #else
    #endif

    struct MonitorInfo {
        vec2ui dimensions;
        vec2i position;
        bool isPrimary;

        #ifdef _WIN32
        HMONITOR handle;
        #else
        #endif
    };

    class Window {
        public:
            Window();
            Window(const String& title);
            Window(u32 width, u32 height);
            Window(const String& title, u32 width, u32 height);
            Window(Window* parent);
            Window(Window* parent, const String& title);
            Window(Window* parent, u32 width, u32 height);
            Window(Window* parent, const String& title, u32 width, u32 height);
            ~Window();

            bool isValid() const;
            bool setTitle(const String& title);
            const String& getTitle() const;
            bool setSize(u32 width, u32 height);
            void getSize(u32* width, u32* height);
            bool setPosition(i32 x, i32 y);
            void getPosition(i32* x, i32* y);
            bool setOpen(bool doOpen);
            bool isOpen() const;
            void setBorderEnabled(bool enabled);
            void subscribe(IInputHandler* inputHandler);
            void unsubscribe(IInputHandler* inputHandler);

            bool pollEvents();

            static Array<MonitorInfo> GetMonitors();

            #ifdef _WIN32
            HWND getHandle();
            #else
            #endif
        
        protected:
            bool m_isOpen;
            String m_title;
            u32 m_width;
            u32 m_height;
            i32 m_posX;
            i32 m_posY;
            Window* m_parent;
            Array<IInputHandler*> m_listeners;

            void onResize();
            void onMove();
            void onClose();
            void onDestroy();
            
            #ifdef _WIN32
            friend LRESULT CALLBACK __windowProc(HWND win, UINT uMsg, WPARAM wParam, LPARAM lParam);
            HWND m_windowHandle;
            bool createWindowHandle_win32();
            bool destroyWindowHandle_win32();
            #else
            #endif
    };
};