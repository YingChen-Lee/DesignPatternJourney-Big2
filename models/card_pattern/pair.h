#pragma once

#include <string>
#include <vector>

#include "card_pattern.h"
#include "../card/card.h"

class Pair : public CardPattern {
public:
    static constexpr std::string kPair = "Pair";

    Pair(const std::vector<Card>& cards);
    
    std::vector<Card> get_cards() const override { return cards_;}
    
    std::optional<Card> GetRepresentiveCard() const override; 

private:
    bool IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    bool IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    
    std::vector<Card> cards_;
};