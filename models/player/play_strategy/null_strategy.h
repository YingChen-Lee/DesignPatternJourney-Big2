#pragma once

#include "play_strategy.h"

#include <memory>

class NullStrategy : public PlayStrategy {
public:
    NullStrategy() : PlayStrategy(nullptr) {}
private:
    bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                         const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
};