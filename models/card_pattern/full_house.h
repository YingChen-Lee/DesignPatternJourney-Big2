#pragma once

#include <memory>
#include <string>
#include <vector>

#include "card_pattern.h"
#include "../card/card.h"

class FullHouse : public CardPattern {
public:
    static constexpr std::string kFullHouse = "FullHouse";
    static bool IsFullHouse(const std::vector<Card>& cards);

    FullHouse(const std::vector<Card>& cards);
    
    std::vector<Card> get_cards() const override { return cards_;}
    
    std::optional<Card> GetRepresentiveCard() const override { return *representive_card_; }

private:
    bool IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    bool IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    
    std::shared_ptr<Card> representive_card_;
    
    std::vector<Card> cards_;
};