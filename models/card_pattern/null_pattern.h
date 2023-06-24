#pragma once

#include <string>

#include "card_pattern.h"

class NullPattern : public CardPattern {
public:
    static constexpr std::string kNullPattern = "-";

    NullPattern() : CardPattern(kNullPattern) {}
    
    std::vector<Card> get_cards() const override { return std::vector<Card>(); }
    
    std::optional<Card> GetRepresentiveCard() const override { return std::nullopt; }

private:
    bool IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
    bool IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const override;
};