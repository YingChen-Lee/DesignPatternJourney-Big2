#include "smallest_first_full_house.h"

#include <algorithm>
#include <cassert>
#include <utility>

#include "../../card_pattern/null_pattern.h"
#include "../../card/rank.h"

#include "strategy_utility.h"

bool SmallestFirstFullHouse::HasValidPlayForThisPattern() {
    // if a rank is in ranks_has_more_than_three_cards_, it must be in ranks_has_more_than_two_cards_
    // so need to check ranks_has_more_than_two_cards_ is >= 2
    return ranks_has_more_than_three_cards_.size() >= 1 &&
           ranks_has_more_than_two_cards_.size() >= 2;
}

bool SmallestFirstFullHouse::CanPlayWithClub3() {
    return ranks_has_more_than_two_cards_[0] == RankEnum::k3;
}

TurnMove SmallestFirstFullHouse::PlayWithClub3(std::shared_ptr<Player> player) {
    return PlaySmallestFullHouse(player, true);
}

TurnMove SmallestFirstFullHouse::PlaySmallest(std::shared_ptr<Player> player) {
    return PlaySmallestFullHouse(player, false);
}

TurnMove SmallestFirstFullHouse::PlaySmallestFullHouse(std::shared_ptr<Player> player, bool should_contain_club_3) {
    RankEnum rank_three_to_play = ranks_has_more_than_three_cards_[0];
    RankEnum rank_pair_to_play = ranks_has_more_than_two_cards_[0] == rank_three_to_play ? 
                                 ranks_has_more_than_two_cards_[1] : 
                                 ranks_has_more_than_two_cards_[0];
    std::vector<Utility::CardIndex> cards_to_play = {rank_to_cards_->at(rank_three_to_play)[0], 
                                                     rank_to_cards_->at(rank_three_to_play)[1],
                                                     rank_to_cards_->at(rank_three_to_play)[2],
                                                     rank_to_cards_->at(rank_pair_to_play)[0],
                                                     rank_to_cards_->at(rank_pair_to_play)[1]};
    if (should_contain_club_3)
        assert(Utility::ContainsClub3(cards_to_play) && "You should have a club 3 if you want to play a Pair with club 3.");
    return Utility::DrawCardsAndPlay(player, cards_to_play);
}

TurnMove SmallestFirstFullHouse::PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) {
    std::optional<Card> top_play_representative = top_play->GetRepresentiveCard();
    assert(top_play_representative.has_value() && "Top play should have a representative card.");

    RankEnum top_play_rank = top_play_representative->get_rank().get();

    // Find if there's three cards with the same rank larger than top_play_rank
    auto three_it = std::find_if(rank_to_cards_->begin(), rank_to_cards_->end(),
                                 [top_play_rank](const auto& rank_cards) { 
                                       return rank_cards.second.size() >= 3 && rank_cards.first > top_play_rank; });
    if (three_it == rank_to_cards_->end())
        return TurnMove::Pass(player);

    RankEnum rank_three_to_play = three_it->first;
    auto pair_it = std::find_if(rank_to_cards_->begin(), rank_to_cards_->end(),
                                 [rank_three_to_play](const auto& rank_cards) { 
                                       return rank_cards.second.size() >= 2 && rank_cards.first != rank_three_to_play; });
    if (pair_it == rank_to_cards_->end())
        return TurnMove::Pass(player);
    else {
        return Utility::DrawCardsAndPlay(player, {three_it->second[0], 
                                                  three_it->second[1],
                                                  three_it->second[2],
                                                  pair_it->second[0],
                                                  pair_it->second[1]});
    }
}

void SmallestFirstFullHouse::CountCardsByRank() {
    for (const auto rank_cards: *rank_to_cards_) {
        if (rank_cards.second.size() >= 2)
            ranks_has_more_than_two_cards_.push_back(rank_cards.first);
        if (rank_cards.second.size() >= 3)
            ranks_has_more_than_three_cards_.push_back(rank_cards.first);
    }
}

void SmallestFirstFullHouse::Preprocess(
        std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) {
    PlayStrategy::Preprocess(rank_to_cards);

    CountCardsByRank();
    std::sort(ranks_has_more_than_two_cards_.begin(), ranks_has_more_than_two_cards_.end());
    std::sort(ranks_has_more_than_three_cards_.begin(), ranks_has_more_than_three_cards_.end());
}

void SmallestFirstFullHouse::Reset() {
    PlayStrategy::Reset();
    ranks_has_more_than_two_cards_.clear();
    ranks_has_more_than_three_cards_.clear();
}