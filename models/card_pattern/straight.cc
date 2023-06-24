#include "straight.h"

#include <algorithm>
#include <cassert>
#include <vector>

#include "../card/card.h"


bool Straight::IsStraight(const std::vector<Card>& cards) {
    if (cards.size() != 5) return false;
    
    std::vector<int> ranks;
    for (const auto& card : cards) 
        ranks.push_back(static_cast<int>(card.get_rank().get()));

    // e.g. ranks = {0, 1, 2, 11, 12}
    std::sort(ranks.begin(), ranks.end());
    std::vector<int> appended_ranks(ranks);
    // appended_ranks = {0, 1, 2, 11, 12, 0, 1, 2, 11, 12}
    std::copy(ranks.begin(), ranks.end(), std::back_inserter(appended_ranks));

    const int total_rank_count = static_cast<int>(RankEnum::kMax);
    for (int start = 0; start < 5; start++){
        bool is_straight = true;
        for (int i = 1; i < 5; i++) {
            if (appended_ranks[start + i] != ((appended_ranks[start + i - 1] + 1) % total_rank_count)) {
                is_straight = false;
                break;
            }
        }
        if (is_straight) return true;
    }
    return false;
}

Straight::Straight(const std::vector<Card>& cards) : cards_(cards), CardPattern(kStraight) {
    assert(Straight::IsStraight(cards_) && "Not valid Straight"); 

    std::sort(cards_.begin(), cards_.end(), [](const Card& lhs, const Card& rhs) {
        return static_cast<int>(lhs.get_rank().get()) < static_cast<int>(rhs.get_rank().get());
    });
    representive_card_ = std::make_shared<Card>(cards_.back());
}

bool Straight::IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return card_pattern_rhs->get_card_pattern_name() == Straight::kStraight;
}

bool Straight::IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    auto straight_rhs = std::dynamic_pointer_cast<Straight>(card_pattern_rhs);
    assert(straight_rhs != nullptr && "card_pattern_rhs must be Straight");
    return *(straight_rhs->representive_card_) < *(this->representive_card_);
}
