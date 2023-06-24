#pragma once

#include "play_strategy.h"
#include "../../card_pattern/null_pattern.h"

#include <memory>

class NullStrategy : public PlayStrategy {
public:
    NullStrategy() : PlayStrategy(nullptr) {}
private:
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) override;

    std::string GetPatternName() {return NullPattern::kNullPattern;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;
};