#pragma once

#include "play_strategy.h"
#include "null_strategy.h"
#include "../../card/rank.h"

#include <memory>
#include <optional>
#include <vector>

#include "strategy_utility.h"

class SmallestFirstStraight : public PlayStrategy {
public:
    SmallestFirstStraight(std::shared_ptr<PlayStrategy> next) : PlayStrategy(next) {}
    SmallestFirstStraight() : PlayStrategy(std::make_shared<NullStrategy>()) {}
private:
    bool IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                   const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                         const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) override;
    
    void GetStartRanksForStraight(const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards);

    std::vector<Utility::CardIndex> GetCardsToPlay(const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards,
                        RankEnum start_rank, std::optional<Utility::CardIndex> representative_card = std::nullopt);

    std::optional<std::pair<RankEnum, Utility::CardIndex>> GetStartRankAndRepresentativeCardIfPossible (
                                    const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards
                                                                            , Card top_play_representative);
    
    void Reset() override;
    
    std::vector<RankEnum> start_ranks_;
};
