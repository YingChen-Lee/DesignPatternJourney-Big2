#include "suit.h"

#include <string>
#include <iostream>

const std::unordered_map<SuitEnum, std::string> Suit::suit_string_map = {
    {SuitEnum::kClub, "♣"}, {SuitEnum::kDiamond, "♦"}, 
    {SuitEnum::kHeart, "♥"}, {SuitEnum::kSpade, "♠"}
};

Suit::Suit(SuitEnum suit): suit_(suit) {};

std::string Suit::ToString() const{
    return Suit::suit_string_map.at(suit_);
}

SuitEnum Suit::get() const{
    return suit_;
}

void Suit::set(SuitEnum suit) {
    suit_ = suit; 
} 

Suit& Suit::operator++(){
    if (suit_ == SuitEnum::kSpade) {
        throw std::out_of_range("for operator ++ Suit");
    }
    set(SuitEnum(static_cast<int>(suit_) + 1));
    return *this;
}

bool Suit::operator==(const Suit& suit_rhs) const{
    return (suit_ == suit_rhs.suit_);
}

int Suit::ShowdownSuit(Suit rhs_suit) const{
    return static_cast<int>(suit_) - static_cast<int>(rhs_suit.get());
}
