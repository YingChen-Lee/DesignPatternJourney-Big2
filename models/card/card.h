#pragma once

#include <string>

#include "rank.h"
#include "suit.h"

class Card {
public:
    Card(Suit, Rank);
    int ShowdownCard(const Card& card_rhs) const;
    Suit get_suit() const;
    Rank get_rank() const;
    std::string ToString() const;
    bool operator<(const Card& card_rhs) const;

private:
    Rank rank_;
    Suit suit_;
};