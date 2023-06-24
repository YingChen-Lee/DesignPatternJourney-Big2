#include "single.h"

bool Single::IsSamePattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    return card_pattern_rhs->get_card_pattern_name() == Single::kSingle;
}

bool Single::IsBiggerSameCardPattern(std::shared_ptr<CardPattern> card_pattern_rhs) const {
    auto single_rhs = std::dynamic_pointer_cast<Single>(card_pattern_rhs);
    return single_rhs->card_ < card_;
}