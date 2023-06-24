#include "pair_parser.h"

#include "../card_pattern/pair.h"

bool PairParser::IsMatched(const std::vector<Card>& cards) const {
    return cards.size() == 2 &&
           cards[0].get_rank() == cards[1].get_rank();
}

std::shared_ptr<CardPattern> PairParser::ParseCardPattern(const std::vector<Card>& cards) const {
    return std::make_shared<Pair>(cards);
}