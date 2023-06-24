#include "full_house_parser.h"

#include "../card_pattern/full_house.h"

bool FullHouseParser::IsMatched(const std::vector<Card>& cards) const {
    return FullHouse::IsFullHouse(cards);
}

std::shared_ptr<CardPattern> FullHouseParser::ParseCardPattern(const std::vector<Card>& cards) const {
    return std::make_shared<FullHouse>(cards);
}