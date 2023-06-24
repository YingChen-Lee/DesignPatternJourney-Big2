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
    Suit(const Suit& suit) = default;
    std::string ToString() const;
    SuitEnum get() const;
    void set(SuitEnum suit);
    Suit& operator++();
    bool operator==(const Suit& suit_rhs) const;
    int ShowdownSuit(Suit rhs_suit) const;
private:
    SuitEnum suit_;
};
