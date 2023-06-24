#include "null_strategy.h"

#include <cassert>

TurnMove NullStrategy::PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) {
    assert(false && "NullStrategy::PlayMatched should never be called");
    return TurnMove::Pass(player);
}

bool NullStrategy::HasValidPlayForThisPattern() {
    assert(false && "NullStrategy::IsMatched should never be called");
    return false;
}

bool NullStrategy::CanPlayWithClub3() {
    assert(false && "NullStrategy::IsMatched should never be called");
    return false;
}
