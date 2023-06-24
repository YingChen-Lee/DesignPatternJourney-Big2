#include "card_pattern_parser.h"

std::shared_ptr<CardPattern> CardPatternParser::Parse(const std::vector<Card>& cards) const {
    if (IsMatched(cards)) {
        return this->ParseCardPattern(cards);
    }
    return next_->Parse(cards);
}