#pragma once

#include "play_strategy.h"
#include "null_strategy.h"

#include <memory>
#include <vector>

#include "strategy_utility.h"

class SmallestFirstPair : public PlayStrategy {
public:
    SmallestFirstPair(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstPair() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                         const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
};