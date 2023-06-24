#pragma once

#include "../../player.h"
#include "../../turn_move.h"
#include "../../turn_info.h"
#include "../../card/card.h"
#include "../../card/rank.h"
#include "strategy_utility.h"

#include <memory>
#include <map>

class PlayStrategy {
public:
    PlayStrategy(std::shared_ptr<PlayStrategy> next) : next_(next) {}
    virtual ~PlayStrategy() = default;
    TurnMove Play(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                  const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards);

protected:
    virtual bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                           const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) = 0;
    virtual TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                                 const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) = 0;

private:
    std::shared_ptr<PlayStrategy> next_;
};