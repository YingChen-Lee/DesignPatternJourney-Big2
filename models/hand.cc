#include "hand.h"

#include <vector>

void Hand::AddCard(std::shared_ptr<const Card> card){
    cards_.push_back(card);
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
