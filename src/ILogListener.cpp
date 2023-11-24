#include <utils/ILogListener.h>
#include <utils/Array.hpp>

#include <stdarg.h>

namespace utils {
    IWithLogging::IWithLogging(const utils::String& scope) : m_scope(scope) {
    }

    IWithLogging::~IWithLogging() {
    }
    
    void IWithLogging::log(LOG_LEVEL level, const utils::String& message) const {
        m_listeners.each([this, level, &message](ILogListener* logger) {
            logger->onLogMessage(level, this->m_scope, message);
        });
    }

    void IWithLogging::log(const char* messageFmt, ...) const {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        log(LOG_INFO, utils::String(out, len));
    }

    void IWithLogging::log(const utils::String& msg) const {
        log(LOG_INFO, msg);
    }

    void IWithLogging::warn(const char* messageFmt, ...) const {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        log(LOG_WARNING, utils::String(out, len));
    }

    void IWithLogging::warn(const utils::String& msg) const {
        log(LOG_WARNING, msg);
    }

    void IWithLogging::error(const char* messageFmt, ...) const {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        log(LOG_ERROR, utils::String(out, len));
    }

    void IWithLogging::error(const utils::String& msg) const {
        log(LOG_ERROR, msg);
    }

    void IWithLogging::fatal(const char* messageFmt, ...) const {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        log(LOG_FATAL, utils::String(out, len));
    }

    void IWithLogging::fatal(const utils::String& msg) const {
        log(LOG_FATAL, msg);
    }

    void IWithLogging::subscribeLogger(ILogListener* logger) {
        bool exists = m_listeners.some([logger](ILogListener* l) { return l == logger; });
        if (exists) return;

        m_listeners.push(logger);
    }

    void IWithLogging::unsubscribeLogger(ILogListener* logger) {
        i64 idx = m_listeners.findIndex([logger](ILogListener* l) { return l == logger; });
        if (idx == -1) return;

        m_listeners.remove(u32(idx));
    }
};