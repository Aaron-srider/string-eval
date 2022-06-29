//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_OPERATOR_H
#define REVERSE_POLISH_NOTATION_OPERATOR_H

#include <iostream>
#include "token/Token.h"
#include "map"

class Operator : public Token {

public:

    bool IsOperator() const override;

    bool IsOperand() const override;

    enum OperatorType {
        ternary,
        binocular,
        unary,
        unknown
    };

    enum OperatorLabel {
        PLUS,
        SUBTRACTION,
        DIVISION,
        MULTIPLICATION,
        NEGATIVE,
        LEFTBRACKET,
        RIGHTBRACKET,
        UNKNOWN
    };

    static std::map<Operator::OperatorLabel, std::string> label_str_map_;

    Operator(OperatorType operator_type, OperatorLabel label);

    static int Build(OperatorLabel label, Operator **new_operator);

    static int Build(const std::string &input, int idx, Operator **new_operator);

    static void IdentifyLabel(const std::string &input, int idx, OperatorLabel *label);

    static bool IsOperator(char ch);

    static bool IsOperand(char ch);

    std::string ToString() const override;

    OperatorLabel GetOperatorLabel() const;

    OperatorType GetOperatorType() const;

    /**
    *
    * @param stack_top_op (, +, -(both subtraction and negative), *, /, not include ')'
    * @param cur_op (, +, -, *, /, not include ')'
    * @return 1 if cur_op has higher priority than stack_top_op, -1 if lower; 0 if err occurs.
    */
    static int Compare(const Operator *stack_top_op, const Operator *cur_op);

    virtual char ToChar() const = 0;

    bool operator==(const Operator *other_op) const;

    bool operator==(Operator::OperatorLabel operator_label) const;

protected:

    OperatorLabel label_ = OperatorLabel::UNKNOWN;

    OperatorType operator_type_ = OperatorType::unknown;

};

#endif //REVERSE_POLISH_NOTATION_OPERATOR_H
