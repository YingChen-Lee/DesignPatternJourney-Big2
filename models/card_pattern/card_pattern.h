#pragma once

#include <memory>
#include <string>
#include <optional>
#include <vector>

#include "../card/card.h"

class CardPattern {
public:
    CardPattern(const std::string& card_pattern_name) : card_pattern_name_(card_pattern_name) {}
    std::string get_card_pattern_name() const { return card_pattern_name_; }
    bool IsBigger(std::shared_ptr<CardPattern> card_pattern_rhs) const;
    
    virtual std::vector<Card> get_cards() const = 0;

    virtual std::optional<Card> GetRepresentiveCard() const = 0;

protected:
    virtual bool IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const = 0;
    virtual bool IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const = 0;

private:
    std::string card_pattern_name_;
};