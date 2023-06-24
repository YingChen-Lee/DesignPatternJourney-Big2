#pragma once

#include <memory>

#include "card_pattern_parser.h"

class NullParser : public CardPatternParser {
public:
    NullParser() : CardPatternParser(nullptr) {}
private:
    bool IsMatched(const std::vector<Card>& cards) const override;
    std::shared_ptr<CardPattern> ParseCardPattern(const std::vector<Card>& cards) const override;
};