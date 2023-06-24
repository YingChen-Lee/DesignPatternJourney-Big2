#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card/rank.h"

#include <memory>
#include <vector>

#include "strategy_utility.h"

class SmallestFirstFullHouse : public PlayStrategy {
public:
    SmallestFirstFullHouse(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstFullHouse() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                         const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    
    void CountCardsByRank(const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards);
    std::vector<RankEnum> ranks_has_more_than_two_cards_;
    std::vector<RankEnum> ranks_has_more_than_three_cards_;
};