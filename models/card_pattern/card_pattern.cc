#include "card_pattern.h"

bool CardPattern::IsBigger(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    if (IsSamePattern(card_pattern_rhs))
        return IsBiggerSameCardPattern(card_pattern_rhs);
    else
        return false;
}