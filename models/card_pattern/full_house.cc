#include "full_house.h"

#include <algorithm>
#include <cassert>
#include <vector>

#include "../card/card.h"


bool FullHouse::IsFullHouse(const std::vector<Card>& cards) {
    if (cards.size() != 5) return false;

    std::vector<int> ranks;
    for (const auto& card : cards) 
        ranks.push_back(static_cast<int>(card.get_rank().get()));

    // e.g. ranks = {1, 1, 1, 11, 11}
    std::sort(ranks.begin(), ranks.end());

    return (ranks[0] == ranks[1] && ranks[1] == ranks[2] && ranks[3] == ranks[4]) ||
           (ranks[0] == ranks[1] && ranks[2] == ranks[3] && ranks[3] == ranks[4]);

}

FullHouse::FullHouse(const std::vector<Card>& cards) : cards_(cards), CardPattern(kFullHouse) {
    assert(FullHouse::IsFullHouse(cards_) && "Not valid FullHouse"); 

    std::sort(cards_.begin(), cards_.end(), [](const Card& lhs, const Card& rhs) {
        return static_cast<int>(lhs.get_rank().get()) < static_cast<int>(rhs.get_rank().get());
    });
    representive_card_ = (cards_[2].get_rank() == cards_[3].get_rank()) ?
                          std::make_shared<Card>(cards_.back()) :
                          std::make_shared<Card>(cards_[2]);
}

bool FullHouse::IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return card_pattern_rhs->get_card_pattern_name() == FullHouse::kFullHouse;
}

bool FullHouse::IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    auto full_house_rhs = std::dynamic_pointer_cast<FullHouse>(card_pattern_rhs);
    assert(full_house_rhs != nullptr && "card_pattern_rhs must be FullHouse");
    return *(full_house_rhs->representive_card_) < *(this->representive_card_);
}
