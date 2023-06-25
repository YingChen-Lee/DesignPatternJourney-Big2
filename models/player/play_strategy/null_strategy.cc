#include "null_strategy.h"

#include <cassert>

bool NullStrategy::HasValidPlayForThisPattern() {
    assert(false && "NullStrategy::IsMatched should never be called");
    return false;
}

bool NullStrategy::CanPlayWithClub3() {
    assert(false && "NullStrategy::IsMatched should never be called");
    return false;
}

TurnMove NullStrategy::PlayWithClub3(std::shared_ptr<Player> player) {
    assert(false && "NullStrategy::PlayWithClub3 should never be called");
    return TurnMove::Pass(nullptr);
}

TurnMove NullStrategy::PlaySmallest(std::shared_ptr<Player> player) {
    assert(false && "NullStrategy::PlaySmallest should never be called");
    return TurnMove::Pass(nullptr);
}

TurnMove NullStrategy::PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) {
    assert(false && "NullStrategy::PlayBiggerThanTopPlayOrPass should never be called");
    return TurnMove::Pass(nullptr); 
}
