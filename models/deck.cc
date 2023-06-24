#include "deck.h"

#include <algorithm>
#include <chrono> 
#include <iostream>
#include <random>
#include <vector>

void Deck::Shuffle(){
    auto rng = std::default_random_engine {};
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(std::begin(cards_), std::end(cards_), rng);
}

std::shared_ptr<const Card> Deck::DrawOneCard(){
    auto top_card = cards_.back();
    cards_.pop_back();
    return top_card;
}

void Deck::PutCard(std::shared_ptr<const Card> card) {
    cards_.push_back(card);
}

int Deck::size() const{
    return cards_.size();
}