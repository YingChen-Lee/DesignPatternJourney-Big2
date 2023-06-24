#include "play_strategy.h"

TurnMove PlayStrategy::Play(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                            const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    TurnMove play = IsMatched(turn_info, player, rank_to_cards) ?
                    PlayMatched(turn_info, player, rank_to_cards) :
                    next_->Play(turn_info, player, rank_to_cards);
    Reset();
    return play;
}