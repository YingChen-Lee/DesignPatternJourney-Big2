#include "null_pattern.h"

bool NullPattern::IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return card_pattern_rhs->get_card_pattern_name() == NullPattern::kNullPattern;
}

bool NullPattern::IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return false;
}