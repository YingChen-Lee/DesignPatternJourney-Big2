#pragma once

#include <string>

#include "card_pattern.h"
#include "../card/card.h"

class Single : public CardPattern {
public:
    static constexpr std::string kSingle = "Single";
    Single(const Card& card) : CardPattern(kSingle), card_(card) {}
    
    std::vector<Card> get_cards() const override { return std::vector<Card>{card_}; }
    
    std::optional<Card> GetRepresentiveCard() const override { return card_; }

private:
    bool IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    bool IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;

    Card card_;
};