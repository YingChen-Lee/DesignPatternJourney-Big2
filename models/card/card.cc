#include "card.h"

#include <cassert>
#include <string>
#include <unordered_map>

Card::Card(Suit suit, Rank rank): suit_(suit), rank_(rank){};

int Card::ShowdownCard(const Card& card_rhs) const {
    int suit_showdown = suit_.ShowdownSuit(card_rhs.get_suit());
    int rank_showdown = rank_.ShowdownRank(card_rhs.get_rank());
    return 4 * rank_showdown + suit_showdown;
}

Suit Card::get_suit() const {
    return suit_;
}

Rank Card::get_rank() const {
    return rank_;
}

std::string Card::ToString() const {
    std::string str = "";
    str += suit_.ToString() + rank_.ToString();
    return str;
} 

bool Card::operator<(const Card& card_rhs) const{
    return (ShowdownCard(card_rhs) < 0);
}

bool Card::operator==(const Card& card_rhs) const{
    return (ShowdownCard(card_rhs) == 0);
}