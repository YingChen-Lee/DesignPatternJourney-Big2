#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card_pattern/pair.h"
#include "strategy_utility.h"

#include <memory>
#include <vector>



class SmallestFirstPair : public PlayStrategy {
public:
    SmallestFirstPair(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstPair() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    std::string GetPatternName() override {return Pair::kPair;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;
    
    TurnMove PlayWithClub3(std::shared_ptr<Player> player) override;
    TurnMove PlaySmallest(std::shared_ptr<Player> player) override;
    TurnMove PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) override;

    TurnMove PlaySmallestPair(std::shared_ptr<Player> player, bool should_contain_club_3);
};