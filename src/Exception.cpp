#include <utils/Exception.h>

#include <stdarg.h>

namespace utils {
    Exception::Exception(const char* fmt, ...) {
        char buf[2048];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, 2048, fmt, args);
        m_message = buf;
        va_end(args);
    }

    Exception::~Exception() {
    }

    const char* Exception::what() const noexcept {
        return m_message.c_str();
    }
}