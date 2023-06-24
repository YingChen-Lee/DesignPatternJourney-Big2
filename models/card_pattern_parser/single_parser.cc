#include "single_parser.h"

#include "../card_pattern/single.h"

bool SingleParser::IsMatched(const std::vector<Card>& cards) const {
    return cards.size() == 1;
}

std::shared_ptr<CardPattern> SingleParser::ParseCardPattern(const std::vector<Card>& cards) const {
    return std::make_shared<Single>(cards[0]);
}