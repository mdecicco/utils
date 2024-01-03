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

    class IWithLogging : public ILogListener {
        public:
            IWithLogging(const utils::String& scope);
            virtual ~IWithLogging();
            
            void propagateLog(LOG_LEVEL level, const utils::String& scope, const utils::String& message);
            void log(LOG_LEVEL level, const utils::String& message);
            void log(const char* messageFmt, ...);
            void log(const utils::String& msg);
            void warn(const char* messageFmt, ...);
            void warn(const utils::String& msg);
            void error(const char* messageFmt, ...);
            void error(const utils::String& msg);
            void fatal(const char* messageFmt, ...);
            void fatal(const utils::String& msg);

            void subscribeLogger(ILogListener* logger);
            void unsubscribeLogger(ILogListener* logger);

            virtual void onLogMessage(LOG_LEVEL level, const utils::String& scope, const utils::String& message);
        
        protected:
            utils::String m_scope;
            utils::Array<ILogListener*> m_listeners;
    };
};