#pragma once

#include "play_strategy.h"
#include "../../card_pattern/null_pattern.h"

#include <memory>

class NullStrategy : public PlayStrategy {
public:
    NullStrategy() : PlayStrategy(nullptr) {}
private:
    std::string GetPatternName() {return NullPattern::kNullPattern;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;
    
    TurnMove PlayWithClub3(std::shared_ptr<Player> player) override;
    TurnMove PlaySmallest(std::shared_ptr<Player> player) override;
    TurnMove PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) override;
};