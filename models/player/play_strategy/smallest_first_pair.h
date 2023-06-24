#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card_pattern/pair.h"
#include "strategy_utility.h"

#include <memory>
#include <vector>



class SmallestFirstPair : public PlayStrategy {
public:
    SmallestFirstPair(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstPair() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) override;
    
    std::string GetPatternName() override {return Pair::kPair;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;
};