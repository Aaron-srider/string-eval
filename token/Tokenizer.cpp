//
// Created by c w on 2022/6/26.
//

#include "Tokenizer.h"
#include "common/CommonUtils.h"

EN_RV Tokenizer::GetInternalTokenList(std::vector<Token *> *copy_list) const{

    for (int i = 0; i < token_list_.size(); i++) {
        Token *cur_token = token_list_.at(i);

        if (cur_token->IsOperator()) {
            Operator *copy_operator;
            Operator::Build(((Operator *) cur_token)->GetOperatorLabel(), &copy_operator);
            copy_list->push_back(copy_operator);
            continue;
        }

        if (cur_token->IsOperand()) {
            copy_list->push_back(new Number(((Number *) cur_token)->ToString()));
            continue;
        }

        return ENR_UNRECOGNIZED_TOKEN;
    }

    return ENR_OK;
}

void Tokenizer::ResetInputSourceString(const std::string *input) {
    std::string result;
    DeleteWhite(input, &result);
    this->input_ = std::move(result);

    token_list_ = std::vector<Token *>();
    idx_ = 0;
}

Tokenizer::Tokenizer() {

}

EN_RV Tokenizer::PeekCurToken(Token **cur_token) const {
    Token *internal_cur_token = token_list_.at(token_list_.size() - 1);
    if (internal_cur_token->IsOperator()) {
        Operator *cur_op = nullptr;
        Operator::Build(((Operator *) internal_cur_token)->GetOperatorLabel(), &cur_op);
        *cur_token = cur_op;
        return ENR_OK;
    }

    if (internal_cur_token->IsOperand()) {
        *cur_token = new Number(internal_cur_token->ToString());
        return ENR_OK;
    }

    return ENR_UNRECOGNIZED_TOKEN;
}
