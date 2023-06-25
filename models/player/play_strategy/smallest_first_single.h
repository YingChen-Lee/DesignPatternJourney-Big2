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
    
    TurnMove PlayWithClub3(std::shared_ptr<Player> player) override;
    TurnMove PlaySmallest(std::shared_ptr<Player> player) override;
    TurnMove PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) override;

    TurnMove PlaySmallestCard(std::shared_ptr<Player> player, bool should_contain_club_3 = false);

    std::optional<Utility::CardIndex> GetFirstLargerCardIndex(const Card& top_card);
};