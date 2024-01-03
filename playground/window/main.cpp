#include <utils/Window.h>
#include <utils/Thread.h>
#include <utils/Allocator.hpp>
#include <utils/Singleton.hpp>
#include <utils/Input.h>

class input : public utils::IInputHandler {
    public:
        input(utils::Window* w) : win(w) {}
        utils::Window* win;

        virtual void onKeyDown(utils::u8 code) {
            win->setTitle(utils::String::Format("key '%c' (%d) down", code, code));
        }
        virtual void onKeyUp(utils::u8 code) {
            win->setTitle(utils::String::Format("key '%c' (%d) up", code, code));
        }
        virtual void onMouseDown(utils::MouseButton buttonIdx) {
            static const char* names[] = {
                "left mouse",
                "middle mouse",
                "right mouse"
            };
            win->setTitle(utils::String::Format("%s down", names[buttonIdx]));
        }
        virtual void onMouseUp(utils::MouseButton buttonIdx) {
            static const char* names[] = {
                "left mouse",
                "middle mouse",
                "right mouse"
            };
            win->setTitle(utils::String::Format("%s up", names[buttonIdx]));
        }
        virtual void onMouseMove(utils::i32 x, utils::i32 y) {
            win->setTitle(utils::String::Format("mouse: %d, %d\n", x, y));
        }
        virtual void onScroll(utils::i32 delta) {
            win->setTitle(utils::String::Format("scroll: %d\n", delta));
        }
};

int main(int argc, const char** argv) {
    utils::Mem::Create();

    {
        utils::Window win, win1(&win);
        win.setOpen(true);
        win1.setOpen(true);

        input i(&win), i1(&win1);
        win.subscribe(&i);
        win1.subscribe(&i1);

        while (win.isOpen()) {
            win.pollEvents();
            win1.pollEvents();
            utils::Thread::Sleep(16);
        }
    }

    utils::Mem::Destroy();

    return 0;
}
