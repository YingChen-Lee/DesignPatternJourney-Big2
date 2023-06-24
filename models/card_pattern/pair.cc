#include "pair.h"

#include <cassert>

#include "../card/card.h"

Pair::Pair(const std::vector<Card>& cards) : CardPattern(kPair), cards_(cards) {
    assert(cards_.size() == 2 && "Pair must have 2 cards");
    assert(cards_[0].get_rank().get() == cards_[1].get_rank().get() && "Pair must have same rank");
}

bool Pair::IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return card_pattern_rhs->get_card_pattern_name() == Pair::kPair;
}

bool Pair::IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    auto pair_rhs = std::dynamic_pointer_cast<Pair>(card_pattern_rhs);
    assert(pair_rhs != nullptr && "card_pattern_rhs must be Pair");
    return pair_rhs->GetRepresentiveCard() < this->GetRepresentiveCard();
}

std::optional<Card> Pair::GetRepresentiveCard() const {
    return (cards_[0] < cards_[1]) ? cards_[1] : cards_[0];
}