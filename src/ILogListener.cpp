#include <utils/ILogListener.h>
#include <utils/Array.hpp>

#include <stdarg.h>

namespace utils {
    IWithLogging::IWithLogging(const utils::String& scope) : m_scope(scope) {
    }

    IWithLogging::~IWithLogging() {
    }
    
    void IWithLogging::propagateLog(LOG_LEVEL level, const utils::String& scope, const utils::String& message) {
        m_listeners.each([level, &scope, &message](ILogListener* logger) {
            logger->onLogMessage(level, scope, message);
        });
    }
    
    void IWithLogging::log(LOG_LEVEL level, const utils::String& message) {
        onLogMessage(level, m_scope, message);
    }

    void IWithLogging::log(const char* messageFmt, ...) {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        onLogMessage(LOG_INFO, m_scope, utils::String(out, len));
    }

    void IWithLogging::log(const utils::String& msg) {
        onLogMessage(LOG_INFO, m_scope, msg);
    }

    void IWithLogging::warn(const char* messageFmt, ...) {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        onLogMessage(LOG_WARNING, m_scope, utils::String(out, len));
    }

    void IWithLogging::warn(const utils::String& msg) {
        onLogMessage(LOG_WARNING, m_scope, msg);
    }

    void IWithLogging::error(const char* messageFmt, ...) {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        onLogMessage(LOG_ERROR, m_scope, utils::String(out, len));
    }

    void IWithLogging::error(const utils::String& msg) {
        onLogMessage(LOG_ERROR, m_scope, msg);
    }

    void IWithLogging::fatal(const char* messageFmt, ...) {
        char out[2048] = { 0 };
        va_list l;
        va_start(l, messageFmt);
        i32 len = vsnprintf(out, 2048, messageFmt, l);
        va_end(l);

        onLogMessage(LOG_FATAL, m_scope, utils::String(out, len));
    }

    void IWithLogging::fatal(const utils::String& msg) {
        onLogMessage(LOG_FATAL, m_scope, msg);
    }

    void IWithLogging::subscribeLogger(ILogListener* logger) {
        if (logger == this) return;

        bool exists = m_listeners.some([logger](ILogListener* l) { return l == logger; });
        if (exists) return;

        m_listeners.push(logger);
    }

    void IWithLogging::unsubscribeLogger(ILogListener* logger) {
        if (logger == this) return;

        i64 idx = m_listeners.findIndex([logger](ILogListener* l) { return l == logger; });
        if (idx == -1) return;

        m_listeners.remove(u32(idx));
    }

    void IWithLogging::onLogMessage(LOG_LEVEL level, const utils::String& scope, const utils::String& message) {
        propagateLog(level, scope, message);
    }
};