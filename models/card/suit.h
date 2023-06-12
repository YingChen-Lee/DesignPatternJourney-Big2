#pragma once

#include <string>
#include <unordered_map>

enum class SuitEnum {
    kClub,
    kDiamond,
    kHeart,
    kSpade
};

class Suit {
public:
    static const std::unordered_map<SuitEnum, std::string> suit_string_map;

    Suit(SuitEnum);
    std::string ToString() const;
    SuitEnum get() const;
    void set(SuitEnum suit);
    Suit& operator++();
    int ShowdownSuit(Suit rhs_suit) const;
private:
    SuitEnum suit_;
};
