#pragma once
#include <string>
#include <format>
#include <vector>
#include <variant>
#include <memory>

namespace brevm
{
    class RuntimeValue
    {
    public:
        virtual ~RuntimeValue() = default;
        virtual std::string toString() const = 0;
        virtual std::string typeName() const = 0;
        virtual bool toBoolean() const = 0;
        virtual std::shared_ptr<RuntimeValue> clone() const = 0;
    };

    class String : public RuntimeValue
    {
        const std::shared_ptr<std::string> value;
    public:
        const std::shared_ptr<std::string>& getValue() const { return value; };
        std::string toString() const override { return *value.get(); };
        std::string typeName() const override { return (std::format("String({}", *value.get()) + ")"); };
        bool toBoolean() const override { return value.get()->size() > 0; }
        std::shared_ptr<RuntimeValue> clone() const override { return std::move(std::make_shared<String>(*value.get())); }
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
        std::shared_ptr<RuntimeValue> clone() const override { return std::move(std::make_shared<Integer>(value)); }
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
        std::shared_ptr<RuntimeValue> clone() const override { return std::move(std::make_shared<Double>(value)); }
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
        std::shared_ptr<RuntimeValue> clone() const override { return std::move(std::make_shared<Boolean>(value)); }
        Boolean(bool v) : value(v) {};
    };

} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.