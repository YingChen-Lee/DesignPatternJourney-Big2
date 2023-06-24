#include "null_strategy.h"

#include <cassert>

bool NullStrategy::IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                             const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    assert(false && "NullStrategy::IsMatched should never be called");
    return false;
}

TurnMove NullStrategy::PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    assert(false && "NullStrategy::PlayMatched should never be called");
    return TurnMove::Pass(player);
}