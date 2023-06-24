#include "null_parser.h"

#include "../card_pattern/null_pattern.h"

bool NullParser::IsMatched(const std::vector<Card>& cards) const {
    // This is the last parser in the chain, so it will always match.
    return true;
}

std::shared_ptr<CardPattern> NullParser::ParseCardPattern(const std::vector<Card>& cards) const {
    return std::make_shared<NullPattern>();
}