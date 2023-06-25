#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card/rank.h"
#include "../../card_pattern/straight.h"
#include "strategy_utility.h"

#include <memory>
#include <optional>
#include <vector>

class SmallestFirstStraight : public PlayStrategy {
public:
    SmallestFirstStraight(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstStraight() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    std::string GetPatternName() override {return Straight::kStraight;}
    bool HasValidPlayForThisPattern() override;
    bool CanPlayWithClub3() override;

    TurnMove PlayWithClub3(std::shared_ptr<Player> player) override;
    TurnMove PlaySmallest(std::shared_ptr<Player> player) override;
    TurnMove PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) override;

    std::vector<Utility::CardIndex> GetCardsToPlay(
                        RankEnum start_rank, std::optional<Utility::CardIndex> representative_card = std::nullopt);

    std::optional<std::pair<RankEnum, Utility::CardIndex>> GetStartRankAndRepresentativeCardIfPossible (
                                                                    Card top_play_representative);
    
    /*
         e.g. rank_to_cards_ = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                                 RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                                 RankEnum::k5 : [(club5, 5)],
                                 RankEnum::k6 : [(heart6, 6)],
                                 RankEnum::k7 : [(spade7, 7)],
                                 RankEnum::k2 : [(diamond2, 8)]}
                             
        3-4-5-6-7 and 2-3-4-5-6
        start_ranks = {RankEnum::k3, RankEnum::k2}
    */
    void GetStartRanksForStraight();

    void Preprocess(std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) override;
    void Reset() override;
    
    std::vector<RankEnum> start_ranks_;
};
