#pragma once

#include "../../player.h"
#include "../../turn_move.h"
#include "../../turn_info.h"
#include "../../card/card.h"
#include "../../card/rank.h"
#include "../../card_pattern/card_pattern.h"
#include "strategy_utility.h"

#include <memory>
#include <map>

class PlayStrategy {
public:
    PlayStrategy(std::shared_ptr<PlayStrategy> next) : next_(next) {}
    virtual ~PlayStrategy() = default;
    TurnMove Play(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                  std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards);

protected:
    virtual void Preprocess(std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) {rank_to_cards_ = rank_to_cards;}
    virtual void Reset() {rank_to_cards_ = nullptr;}
    
    virtual std::string GetPatternName() = 0;
    virtual bool HasValidPlayForThisPattern() = 0;
    virtual bool CanPlayWithClub3() = 0;

    virtual TurnMove PlayWithClub3(std::shared_ptr<Player> player) = 0;
    virtual TurnMove PlaySmallest(std::shared_ptr<Player> player) = 0;
    virtual TurnMove PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) = 0;

    std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards_ = nullptr;

private:
    bool IsMatched(const TurnInfo& turn_info);
    TurnMove PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player);

    std::shared_ptr<PlayStrategy> next_;
};