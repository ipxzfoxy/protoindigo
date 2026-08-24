#pragma once
#include <string>
#include <format>
#include <vector>
#include <variant>
#include <memory>

namespace brevm::spec
{
    class RuntimeValue
    {
    public:
        virtual ~RuntimeValue() = default;
        virtual std::string toString() const = 0;
        virtual std::string typeName() const = 0;
        virtual bool toBoolean() const = 0;
    };

    class Sequence : public RuntimeValue
    {
        std::vector<uint8_t> value;
    public:
        std::vector<uint8_t> getValue() const { return value; };
        std::string toString() const override { return "[Wave Sequence]"; };
        std::string typeName() const override { return "Sequence([Wave Sequence])"; };
        bool toBoolean() const override { return value.size() > 0; }
        int size() const { return value.size(); }
    };

    class String : public RuntimeValue
    {
        const std::shared_ptr<std::string> value;
        
    public:
        const std::shared_ptr<std::string>& getValue() const { return value; };
        std::string toString() const override { return *value.get(); };
        std::string typeName() const override { return (std::format("String({}", *value.get()) + ")"); };
        bool toBoolean() const override { return value.get()->size() > 0; }
        String(std::string v) : value(std::make_shared<std::string>(std::move(v))) {};
    };

    class Integer : public RuntimeValue
    {
        int value;
    public:
        int getValue() const { return value; };
        std::string toString() const override { return std::to_string(value); };
        std::string typeName() const override { return (std::format("Integer({}", toString()) + ")"); };
        bool toBoolean() const override { return value > 0; }
        Integer(int v) : value(v) {};
    };

    class Double : public RuntimeValue
    {
        double value;
    public:
        double getValue() const { return value; };
        std::string toString() const override { return std::to_string(value); };
        std::string typeName() const override { return (std::format("Integer({}", toString()) + ")"); };
        bool toBoolean() const override { return value > 0; }
        Double(double v) : value(v) {};
    };

    class Boolean : public RuntimeValue
    {
        bool value;
    public:
        bool getValue() const { return value; };
        std::string toString() const override { return std::to_string(value); };
        std::string typeName() const override { return (std::format("Integer({}", toString()) + ")"); };
        bool toBoolean() const override { return value; }
        Boolean(bool v) : value(v) {};
    };

} // namespace wave::internal
