#pragma once
#include <utils/Types.h>
#include <utils/String.h>
#include <utils/Array.h>

namespace utils {
    enum LOG_LEVEL {
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
        LOG_FATAL
    };

    class ILogListener {
        public:
            virtual void onLogMessage(LOG_LEVEL level, const utils::String& scope, const utils::String& message) = 0;
    };

    class IWithLogging {
        public:
            IWithLogging(const utils::String& scope);
            virtual ~IWithLogging();

            void log(LOG_LEVEL level, const utils::String& message) const;
            void log(const char* messageFmt, ...) const;
            void log(const utils::String& msg) const;
            void warn(const char* messageFmt, ...) const;
            void warn(const utils::String& msg) const;
            void error(const char* messageFmt, ...) const;
            void error(const utils::String& msg) const;
            void fatal(const char* messageFmt, ...) const;
            void fatal(const utils::String& msg) const;

            void subscribeLogger(ILogListener* logger);
            void unsubscribeLogger(ILogListener* logger);
        
        protected:
            utils::String m_scope;
            utils::Array<ILogListener*> m_listeners;
    };
};