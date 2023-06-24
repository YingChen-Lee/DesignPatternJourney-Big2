#include "play_strategy.h"
#include "../../card_pattern/null_pattern.h"

TurnMove PlayStrategy::Play(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                            std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) {
    Preprocess(rank_to_cards);

    TurnMove play = IsMatched(turn_info) ?
                    PlayMatched(turn_info, player) :
                    next_->Play(turn_info, player, rank_to_cards);

    Reset();
    return play;
}

bool PlayStrategy::IsMatched(const TurnInfo& turn_info) {
    // You have no choice but to play the same pattern if top play is not Null
    if (turn_info.top_play->get_card_pattern_name() == GetPatternName())
        return true;
    else if (turn_info.top_play->get_card_pattern_name() != NullPattern::kNullPattern)
        return false;
        
    // top play is Null, so you can play this pattern if you have it
    if (!HasValidPlayForThisPattern())
        return false;
    
    if (turn_info.should_contain_club_3)
        return CanPlayWithClub3();

    return true;
}