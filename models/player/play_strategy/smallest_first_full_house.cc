#include "smallest_first_full_house.h"

#include <algorithm>
#include <cassert>
#include <utility>

#include "../../card_pattern/full_house.h"
#include "../../card_pattern/null_pattern.h"
#include "../../card/rank.h"

#include "strategy_utility.h"

/*
 e.g. rank_to_cards_ = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                         RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                         RankEnum::k5 : [(club5, 5)]}

    ranks_has_more_than_two_cards_ = [RankEnum::k3, RankEnum::k4]
    ranks_has_more_than_three_cards_ = [RankEnum::k4]
*/
void SmallestFirstFullHouse::CountCardsByRank(const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    for (const auto rank_cards: rank_to_cards) {
        if (rank_cards.second.size() >= 2)
            ranks_has_more_than_two_cards_.push_back(rank_cards.first);
        if (rank_cards.second.size() >= 3)
            ranks_has_more_than_three_cards_.push_back(rank_cards.first);
    }
}

bool SmallestFirstFullHouse::IsMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                            const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    // You have no choice but to play FullHouse if top play is a FullHouse
    if (turn_info.top_play->get_card_pattern_name() == FullHouse::kFullHouse)
        return true;
    else if (turn_info.top_play->get_card_pattern_name() != NullPattern::kNullPattern)
        return false;
    
    CountCardsByRank(rank_to_cards);
    std::sort(ranks_has_more_than_two_cards_.begin(), ranks_has_more_than_two_cards_.end());
    std::sort(ranks_has_more_than_three_cards_.begin(), ranks_has_more_than_three_cards_.end());
    
    // if a rank is in ranks_has_more_than_three_cards_, it must be in ranks_has_more_than_two_cards_
    // so need to check ranks_has_more_than_two_cards_ is >= 2
    bool has_full_house = ranks_has_more_than_three_cards_.size() >= 1 &&
                          ranks_has_more_than_two_cards_.size() >= 2;
    if (!has_full_house)
        return false;
    if (turn_info.should_contain_club_3) {
        // Need to check if there's any full_house for Rank 3 if you want to play a FullHouse in the 
        // first play of the first round
        if (ranks_has_more_than_two_cards_[0] != RankEnum::k3)
            return false;
    }
    return true;
}

TurnMove SmallestFirstFullHouse::PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player,
                                        const std::map<RankEnum, std::vector<Utility::CardIndex>>& rank_to_cards) {
    if (turn_info.should_contain_club_3) { 
        assert(Utility::ContainsClub3({rank_to_cards.at(RankEnum::k3)[0].get_card()}) &&
                "You should have a club 3 if you want to play a Pair with club 3.");
        if (ranks_has_more_than_three_cards_[0] == RankEnum::k3) {
            // It's guranteed that ranks_has_more_than_two_cards_[0] is RankEnum::k3
            RankEnum rank_pair_to_play = ranks_has_more_than_two_cards_[1];
            return Utility::DrawCardsAndPlay(player, {rank_to_cards.at(RankEnum::k3)[0], 
                                                      rank_to_cards.at(RankEnum::k3)[1],
                                                      rank_to_cards.at(RankEnum::k3)[2],
                                                      rank_to_cards.at(rank_pair_to_play)[0],
                                                      rank_to_cards.at(rank_pair_to_play)[1]});
        } else {
            RankEnum rank_three_to_play = ranks_has_more_than_three_cards_[0];
            return Utility::DrawCardsAndPlay(player, {rank_to_cards.at(RankEnum::k3)[0], 
                                                      rank_to_cards.at(RankEnum::k3)[1],
                                                      rank_to_cards.at(rank_three_to_play)[0],
                                                      rank_to_cards.at(rank_three_to_play)[1],
                                                      rank_to_cards.at(rank_three_to_play)[2]});
        }
    }

    // has no top play, so can play any full_house
    if (turn_info.top_play->get_card_pattern_name() == NullPattern::kNullPattern) {
        RankEnum rank_three_to_play = ranks_has_more_than_three_cards_[0];
        RankEnum rank_pair_to_play = ranks_has_more_than_two_cards_[0] == rank_three_to_play ? 
                                     ranks_has_more_than_two_cards_[1] : 
                                     ranks_has_more_than_two_cards_[0];
        return Utility::DrawCardsAndPlay(player, {rank_to_cards.at(rank_three_to_play)[0], 
                                                  rank_to_cards.at(rank_three_to_play)[1],
                                                  rank_to_cards.at(rank_three_to_play)[2],
                                                  rank_to_cards.at(rank_pair_to_play)[0],
                                                  rank_to_cards.at(rank_pair_to_play)[1]});
    }

    // Has top play, so need to play a full_house bigger than it
    std::optional<Card> top_play_representative = turn_info.top_play->GetRepresentiveCard();
    assert(top_play_representative.has_value() && "Top play should have a representative card.");

    RankEnum top_play_rank = top_play_representative->get_rank().get();

    // Find if there's three cards with the same rank larger than top_play_rank
    auto three_it = std::find_if(rank_to_cards.begin(), rank_to_cards.end(),
                                 [top_play_rank](const auto& rank_cards) { 
                                       return rank_cards.second.size() >= 3 && rank_cards.first > top_play_rank; });
    if (three_it == rank_to_cards.end())
        return TurnMove::Pass(player);

    RankEnum rank_three_to_play = three_it->first;
    auto pair_it = std::find_if(rank_to_cards.begin(), rank_to_cards.end(),
                                 [rank_three_to_play](const auto& rank_cards) { 
                                       return rank_cards.second.size() >= 2 && rank_cards.first != rank_three_to_play; });
    if (pair_it == rank_to_cards.end())
        return TurnMove::Pass(player);
    else {
        return Utility::DrawCardsAndPlay(player, {three_it->second[0], 
                                                  three_it->second[1],
                                                  three_it->second[2],
                                                  pair_it->second[0],
                                                  pair_it->second[1]});
    }
}