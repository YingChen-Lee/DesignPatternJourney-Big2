#include "straight_parser.h"

#include "../card_pattern/straight.h"

bool StraightParser::IsMatched(const std::vector<Card>& cards) const {
    return Straight::IsStraight(cards);
}

std::shared_ptr<CardPattern> StraightParser::ParseCardPattern(const std::vector<Card>& cards) const {
    return std::make_shared<Straight>(cards);
}