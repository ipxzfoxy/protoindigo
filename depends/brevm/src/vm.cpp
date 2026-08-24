/**
 * Implements of BreVM methods (vm.h)
 * vm.cpp
 * 
 * Implementation of brevm::VM methods, and constructor and more.
 * Register operations following the BreVM Specification.
 */
#include "include/vm.h"

namespace brevm
{
    VM::VM(spec::constantPool cp)
        : memory(std::move(cp)) {};

    /**
     * =============== ADD ===============
     * String, String -> String
     * Integer, String -> String
     * Double, String -> String
     * Boolean, String -> String
     * Integer, Integer -> Integer
     * Integer, Double -> Double
     * Double, Double -> Double
     * ------------------------------------
     * Otherwise, the operation will not be performed. The order of the values does not matter
     * in the ADD operation, except when concatenating values with a string.
    */

    std::shared_ptr<spec::RuntimeValue> VM::add(
            const spec::reg& left,
            const spec::reg& right
    )
    {
        // Case left isA String
        if (auto leftString = dynamic_cast<spec::String*>(left.get()))
        {
            // ADD String, String: -> String
            if (auto rightString = dynamic_cast<spec::String*>(right.get()))
            {
                return std::make_shared<spec::String>(*(leftString->getValue().get()) + *(rightString->getValue().get()));
            }
            // ADD String, Integer: -> String
            if (auto rightInteger = dynamic_cast<spec::Integer*>(right.get()))
            {
                return std::make_shared<spec::String>(*(leftString->getValue().get()) + rightInteger->toString());
            }

            // ADD String, Double: -> String
            if (auto rightDouble = dynamic_cast<spec::Double*>(right.get()))
            {
                return std::make_shared<spec::String>(*(leftString->getValue().get()) + rightDouble->toString());
            }

            // ADD String, Boolean: -> String
            if (auto rightBoolean = dynamic_cast<spec::Boolean*>(right.get()))
            {
                return std::make_shared<spec::String>(*(leftString->getValue().get()) + rightBoolean->toString());
            }
        }

        // Case left isA Integer
        if (auto leftInteger = dynamic_cast<spec::Integer*>(left.get()))
        {
            // ADD Integer, String: -> String
            if (auto rightString = dynamic_cast<spec::String*>(right.get()))
            {
                return std::make_shared<spec::String>(leftInteger->toString() + *(rightString->getValue().get()));
            }
            // ADD Integer, Integer: -> Integer
            if (auto rightInteger = dynamic_cast<spec::Integer*>(right.get()))
            {
                return std::make_shared<spec::Integer>(leftInteger->getValue() + rightInteger->getValue());
            }
            // ADD Integer, Double: -> Double
            if (auto rightDouble = dynamic_cast<spec::Double*>(right.get()))
            {
                return std::make_shared<spec::Double>(leftInteger->getValue() + rightDouble->getValue());
            }
        }

        // Case left isA Double
        if (auto leftDouble = dynamic_cast<spec::Double*>(left.get()))
        {
            // ADD Double, String: -> String
            if (auto rightString = dynamic_cast<spec::String*>(right.get()))
            {
                return std::make_shared<spec::String>(leftDouble->toString() + *(rightString->getValue().get()));
            }
            // ADD Double, Integer: -> Double
            if (auto rightInteger = dynamic_cast<spec::Integer*>(right.get()))
            {
                return std::make_shared<spec::Double>(leftDouble->getValue() + rightInteger->getValue());
            }
            // ADD Double, Double: -> Double
            if (auto rightDouble = dynamic_cast<spec::Double*>(right.get()))
            {
                return std::make_shared<spec::Double>(leftDouble->getValue() + rightDouble->getValue());
            }
        }

        throw error::Error(std::format(
            "TypeError: Invalid operands for ADD: {} and {}.", left.get()->typeName(), right.get()->typeName()
        ));
    };


    /**
     * =============== SUB ===============
     * Integer, Integer -> Integer
     * Double, Double -> Double
     * Double, Integer -> Double
     * ------------------------------------
    */
    std::shared_ptr<spec::RuntimeValue> VM::sub(
            const spec::reg& left,
            const spec::reg& right
    )
    {
        // Case left isA Integer
        if (auto leftInteger = dynamic_cast<Integer*>(left.get()))
        {
            // SUB Integer, Integer -> Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Integer>(leftInteger->getValue() - rightInteger->getValue());
            }
            // SUB Integer, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftInteger->getValue() - rightDouble->getValue());
            }
        }

        // Case left isA Double -> Double
        if (auto leftDouble = dynamic_cast<Double*>(left.get()))
        {
            // SUB Double, Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() - rightInteger->getValue());
            }
            // SUB Double, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() - rightDouble->getValue());
            }
        }
        throw error::Error(std::format(
            "TypeError: Invalid operands for SUB: {} and {}.", left.get()->typeName(), right.get()->typeName()
        ));
    }

    /**
     * =============== MUL ===============
     * Integer, Integer -> Integer
     * Double, Double -> Double
     * Double, Integer -> Double
     * ------------------------------------
    */
    std::shared_ptr<spec::RuntimeValue> VM::mul(
            const spec::reg& left,
            const spec::reg& right
    )
    {
        // Case left isA Integer
        if (auto leftInteger = dynamic_cast<Integer*>(left.get()))
        {
            // SUB Integer, Integer -> Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Integer>(leftInteger->getValue() * rightInteger->getValue());
            }
            // SUB Integer, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftInteger->getValue() * rightDouble->getValue());
            }
        }

        // Case left isA Double -> Double
        if (auto leftDouble = dynamic_cast<Double*>(left.get()))
        {
            // SUB Double, Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() * rightInteger->getValue());
            }
            // SUB Double, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() * rightDouble->getValue());
            }
        }
        throw error::Error(std::format(
            "TypeError: Invalid operands for MUL: {} and {}.", left.get()->typeName(), right.get()->typeName()
        ));
    }
    /**
     * =============== DIV ===============
     * Integer, Integer -> Integer
     * Double, Double -> Double
     * Double, Integer -> Double
     * ------------------------------------
    */
    std::shared_ptr<spec::RuntimeValue> VM::div(
            const spec::reg& left,
            const spec::reg& right
    )
    {
        // Case left isA Integer
        if (auto leftInteger = dynamic_cast<Integer*>(left.get()))
        {
            // SUB Integer, Integer -> Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Integer>(leftInteger->getValue() / rightInteger->getValue());
            }
            // SUB Integer, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftInteger->getValue() / rightDouble->getValue());
            }
        }

        // Case left isA Double -> Double
        if (auto leftDouble = dynamic_cast<Double*>(left.get()))
        {
            // SUB Double, Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() / rightInteger->getValue());
            }
            // SUB Double, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(leftDouble->getValue() / rightDouble->getValue());
            }
        }
        throw error::Error(std::format(
            "TypeError: Invalid operands for DIV: {} and {}.", left.get()->typeName(), right.get()->typeName()
        ));
    }
    /**
     * =============== MOD ===============
     * Integer, Integer -> Integer
     * Double, Double -> Double
     * Double, Integer -> Double
     * ------------------------------------
    */
    std::shared_ptr<spec::RuntimeValue> VM::mod(
            const spec::reg& left,
            const spec::reg& right
    )
    {
        // Case left isA Integer
        if (auto leftInteger = dynamic_cast<Integer*>(left.get()))
        {
            // SUB Integer, Integer -> Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Integer>(std::fmod(leftInteger->getValue(), rightInteger->getValue()));
            }
            // SUB Integer, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(std::fmod(leftInteger->getValue(), rightDouble->getValue()));
            }
        }

        // Case left isA Double -> Double
        if (auto leftDouble = dynamic_cast<Double*>(left.get()))
        {
            // SUB Double, Integer
            if (auto rightInteger = dynamic_cast<Integer*>(right.get()))
            {
                return std::make_shared<Double>(std::fmod(leftDouble->getValue(), rightInteger->getValue()));
            }
            // SUB Double, Double
            if (auto rightDouble = dynamic_cast<Double*>(right.get()))
            {
                return std::make_shared<Double>(std::fmod(leftDouble->getValue(), rightDouble->getValue()));
            }
        }
        throw error::Error(std::format(
            "TypeError: Invalid operands for MOD: {} and {}.", left.get()->typeName(), right.get()->typeName()
        ));
    }
} // namespace brevm
