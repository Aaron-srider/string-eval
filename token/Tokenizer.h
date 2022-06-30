//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_TOKENIZER_H
#define REVERSE_POLISH_NOTATION_TOKENIZER_H

#include"MacroStatus.h"
#include "string"
#include "Token.h"
#include "vector"
#include "token/operator/Operator.h"
#include "token/operand/Number.h"
#include "map"

class Tokenizer {

public:

    Tokenizer();

    explicit Tokenizer(std::string input) : idx_(0), input_(std::move(input)) {
    }

    EN_RV PeekCurToken(Token** cur_token) const;

    // if next end, return nullptr; return value need to be deleted when not used.
    EN_RV NextToken(Token **next_token) {

        if (idx_ >= input_.size()) {
            return ENR_END;
        }

        if (input_.at(idx_) == '+' ||
            input_.at(idx_) == '-' ||
            input_.at(idx_) == '*' ||
            input_.at(idx_) == '/' ||
            input_.at(idx_) == '(' ||
            input_.at(idx_) == ')') {
            Operator *op;
            Operator::Build(input_, idx_, &op);
            *next_token = op;

            Operator::Build(input_, idx_, &op);
            this->token_list_.push_back(op);

            idx_++;

            if (idx_ >= input_.size()) {
                return ENR_END;
            }
            return ENR_OK;
        }

        if (Number::IsPositiveInt(input_.at(idx_))) {
            std::string integer;
            while (idx_ < input_.size() && Number::IsPositiveInt(input_.at(idx_))) {
                integer.push_back(input_.at(idx_));
                idx_++;
            }
            *next_token = new Number(integer);
            this->token_list_.push_back(new Number(integer));
            if (idx_ >= input_.size()) {
                return ENR_END;
            }

            return ENR_OK;
        }
        *next_token = nullptr;
        return ENR_UNRECOGNIZED_TOKEN;
    }

    // if next end, return nullptr; return value need to be deleted when not used.
    EN_RV PeekNext(Token **next_token) {

        if (idx_ >= input_.size()) {
            return ENR_END;
        }

        if (input_.at(idx_) == '+' ||
            input_.at(idx_) == '-' ||
            input_.at(idx_) == '*' ||
            input_.at(idx_) == '/' ||
            input_.at(idx_) == '(' ||
            input_.at(idx_) == ')') {
            Operator *op;
            Operator::Build(input_, idx_, &op);
            *next_token = op;
            if (idx_ + 1 >= input_.size()) {
                return ENR_END;
            }
            return ENR_OK;
        }

        if (Number::IsPositiveInt(input_.at(idx_))) {
            std::string integer;
            int idx_temp = idx_;
            while (idx_temp < input_.size() && Number::IsPositiveInt(input_.at(idx_temp))) {
                integer.push_back(input_.at(idx_temp));
                idx_temp++;
            }
            *next_token = new Number(integer);
            if (idx_temp >= input_.size()) {
                return ENR_END;
            }

            return ENR_OK;
        }
        *next_token = nullptr;
        return ENR_UNRECOGNIZED_TOKEN;
    }

    void SetInput(std::string input);

    EN_RV GetInternalTokenList(std::vector<Token *> *copy_list);
private:
    std::string input_;

    int idx_;

    std::vector<Token *> token_list_;


};


#endif //REVERSE_POLISH_NOTATION_TOKENIZER_H
