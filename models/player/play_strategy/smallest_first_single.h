#pragma once

#include "play_strategy.h"
#include "null_strategy.h"

#include "../../card_pattern/single.h"

#include <memory>

class SmallestFirstSingle : public PlayStrategy {
public:
    SmallestFirstSingle(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstSingle() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    std::string GetPatternName() override {return Single::kSingle;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;

    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) override;

    std::optional<Utility::CardIndex> GetFirstLargerCardIndex(const Card& top_card);
};