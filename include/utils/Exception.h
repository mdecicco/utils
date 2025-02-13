#pragma once
#include <utils/Types.h>
#include <utils/String.h>
#include <exception>

namespace utils {
    class Exception : public std::exception {
        public:
            Exception(const char* fmt, ...);
            virtual ~Exception();

            virtual const char* what() const noexcept;

        protected:
            String m_message;
    };
};