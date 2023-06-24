#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card/rank.h"
#include "../../card_pattern/full_house.h"

#include <memory>
#include <vector>

#include "strategy_utility.h"

class SmallestFirstFullHouse : public PlayStrategy {
public:
    SmallestFirstFullHouse(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstFullHouse() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) override;
    
    std::string GetPatternName() override {return FullHouse::kFullHouse;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;
    
    void Preprocess(std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) override;
    void Reset() override;
    
    /*
    e.g. rank_to_cards_ = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                            RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                            RankEnum::k5 : [(club5, 5)]}

    ranks_has_more_than_two_cards_ = [RankEnum::k3, RankEnum::k4]
    ranks_has_more_than_three_cards_ = [RankEnum::k4]
    */
    void CountCardsByRank();
    std::vector<RankEnum> ranks_has_more_than_two_cards_;
    std::vector<RankEnum> ranks_has_more_than_three_cards_;
};