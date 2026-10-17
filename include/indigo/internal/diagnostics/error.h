#pragma once

#include <string>
#include <exception>

namespace bre::internal
{
    class Error : public std::exception
    {
    protected:
        std::string _message;

    public:
        explicit Error(const std::string& m);

        virtual std::string name();
        virtual std::string message();
        virtual std::string detail();
    };

    class NFError : public Error
    {
    private:
        std::string target;
        std::string _detail;

    public:
        explicit NFError(const std::string& t);

        std::string name() override;
        std::string message() override;
        std::string detail() override;
    };
}