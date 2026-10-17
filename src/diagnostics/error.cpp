#include "indigo/internal/diagnostics/error.h"

namespace bre::internal
{
    Error::Error(const std::string& m)
        : _message(m)
    {}

    std::string Error::name()
    {
        return "Error";
    }

    std::string Error::message()
    {
        return _message;
    }

    std::string Error::detail()
    {
        return "";
    }


    NFError::NFError(const std::string& t)
        : Error("File not found"),
          target(t),
          _detail("Cannot find\n--> " + t)
    {}

    std::string NFError::name()
    {
        return "NFError";
    }

    std::string NFError::message()
    {
        return _message;
    }

    std::string NFError::detail()
    {
        return _detail;
    }
}