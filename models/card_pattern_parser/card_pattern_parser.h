#pragma once

#include <memory>
#include <vector>

#include "../card/card.h"
#include "../card_pattern/card_pattern.h"

//TTIIIMMM
#include <iostream>

class CardPatternParser {
public:
    CardPatternParser(std::shared_ptr<CardPatternParser> next) : next_(next) {}

    std::shared_ptr<CardPattern> Parse(const std::vector<Card>& cards) const;
    
protected:
    virtual bool IsMatched(const std::vector<Card>& cards) const = 0;
    virtual std::shared_ptr<CardPattern> ParseCardPattern(const std::vector<Card>& cards) const = 0;

private:
    std::shared_ptr<CardPatternParser> next_;
};