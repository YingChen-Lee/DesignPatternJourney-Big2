#include "hand.h"

#include <algorithm>
#include <vector>

void Hand::AddCard(std::shared_ptr<const Card> card){
    cards_.push_back(card);
    Sort();
}

std::vector<std::shared_ptr<const Card>> Hand::get_cards() const{
    return cards_;
}

std::shared_ptr<const Card> Hand::DrawCard(int index) {
    auto card = cards_[index];
    cards_.erase(cards_.begin() + index);
    return card;
}

int Hand::get_size() const {
    return cards_.size();
}

void Hand::Reset() {
    cards_.clear();
}

bool Hand::HasClub3() const {
    for (const auto& card : cards_) {
        if (card->get_suit().get() == SuitEnum::kClub && card->get_rank().get() == RankEnum::k3)
            return true;
    }
    return false;
}

void Hand::Sort() {
    std::sort(cards_.begin(), cards_.end(), [](std::shared_ptr<const Card> a, std::shared_ptr<const Card> b) {
        return *a < *b;
    });
}