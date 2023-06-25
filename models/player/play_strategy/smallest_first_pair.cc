#include "smallest_first_pair.h"

#include <algorithm>
#include <cassert>
#include <utility>

#include "../../card_pattern/null_pattern.h"
#include "../../card/rank.h"

#include "strategy_utility.h"

/*
        key-value         first(key)            second(value)
 e.g. rank_to_cards_ = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                         RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                         ...]}
*/

bool SmallestFirstPair::HasValidPlayForThisPattern() {
    return std::any_of(rank_to_cards_->begin(), rank_to_cards_->end(), 
                           [](const auto& rank_cards) { return rank_cards.second.size() >= 2; });
}

bool SmallestFirstPair::CanPlayWithClub3() {
    // Need to check if there's any pair for Rank 3 if you want to play a Pair in the 
    return rank_to_cards_->find(RankEnum::k3) != rank_to_cards_->end() && 
           rank_to_cards_->at(RankEnum::k3).size() >= 2;
}

TurnMove SmallestFirstPair::PlayWithClub3(std::shared_ptr<Player> player) {
    return PlaySmallestPair(player, true); 
}

TurnMove SmallestFirstPair::PlaySmallest(std::shared_ptr<Player> player) {
    return PlaySmallestPair(player, false);
}

TurnMove SmallestFirstPair::PlaySmallestPair(std::shared_ptr<Player> player, bool should_contain_club_3) {
    auto it = std::find_if(rank_to_cards_->begin(), rank_to_cards_->end(), 
                   [](const auto& rank_cards) { return rank_cards.second.size() >= 2; });
    assert((it != rank_to_cards_->end()) && "You should have a pair if you want to play a Pair.");
    // get the smallest rank, and retrieve the first two cards of that rank
    std::vector<Utility::CardIndex> cards_to_play = {it->second[0], it->second[1]};

    if (should_contain_club_3)
        assert(Utility::ContainsClub3(cards_to_play) && "You should have a club 3 if you want to play a Pair with club 3.");
    return Utility::DrawCardsAndPlay(player, cards_to_play);
}

TurnMove SmallestFirstPair::PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) {
    std::optional<Card> top_play_representative = top_play->GetRepresentiveCard();
    assert(top_play_representative.has_value() && "Top play should have a representative card.");

    RankEnum top_play_rank = top_play_representative->get_rank().get();

    /*
      Try to play a pair with the same rank as top play. 
      Note that there are at most 2 cards in this rank because top play already has 2 cards.
      
      If you cannot play a pair with the same rank, then find the smallest rank that is larger than top play.
    */
    auto has_2_cards_in_rank([this](RankEnum rank) { 
        return rank_to_cards_->find(rank) != rank_to_cards_->end() && 
               rank_to_cards_->at(rank).size() == 2; 
    });

    if (has_2_cards_in_rank(top_play_rank) && 
        (*(top_play_representative) < rank_to_cards_->at(top_play_rank)[1].get_card())) {
        return Utility::DrawCardsAndPlay(player, {rank_to_cards_->at(top_play_rank)[0], rank_to_cards_->at(top_play_rank)[1]});
    } else {
        auto first_bigger_it = std::find_if(rank_to_cards_->begin(), rank_to_cards_->end(),
                                [top_play_rank](const auto& rank_cards) { 
                                    return rank_cards.second.size() >= 2 && rank_cards.first > top_play_rank; });
        if (first_bigger_it != rank_to_cards_->end())
            return Utility::DrawCardsAndPlay(player, {first_bigger_it->second[0], first_bigger_it->second[1]});
        else
            return TurnMove::Pass(player);
    }
}
