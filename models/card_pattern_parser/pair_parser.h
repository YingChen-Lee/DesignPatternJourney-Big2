#pragma once

#include <memory>

#include "card_pattern_parser.h"
#include "null_parser.h"

class PairParser : public CardPatternParser {
public:
    PairParser(std::shared_ptr<CardPatternParser> next) : CardPatternParser(next) {}
    PairParser() : CardPatternParser(std::make_shared<NullParser>()) {}
private:
    bool IsMatched(const std::vector<Card>& cards) const override;
    std::shared_ptr<CardPattern> ParseCardPattern(const std::vector<Card>& cards) const override;
};