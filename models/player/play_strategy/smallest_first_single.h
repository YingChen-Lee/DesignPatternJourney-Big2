#pragma once

#include "play_strategy.h"
#include "null_strategy.h"

#include <memory>

class SmallestFirstSingle : public PlayStrategy {
public:
    SmallestFirstSingle(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstSingle() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                         const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;

    std::optional<Utility::CardIndex> GetFirstLargerCardIndex(const Card& top_card,
                        const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards);
};