#include "smallest_first_straight.h"

#include <algorithm>
#include <deque>
#include <cassert>
#include <utility>
#include <unordered_set>
#include <utility>

#include "../../card_pattern/null_pattern.h"
#include "../../card/rank.h"

#include "strategy_utility.h"

namespace {
const int kTotalRankCount = static_cast<int>(RankEnum::kMax);

RankEnum GetRepresentativeRank(RankEnum start_rank) {
    return static_cast<RankEnum>(std::max(static_cast<int>(start_rank) + 4, kTotalRankCount - 1));
}
}  // namespace

bool SmallestFirstStraight::HasValidPlayForThisPattern() {
    return !start_ranks_.empty();
}

bool SmallestFirstStraight::CanPlayWithClub3() {
    std::unordered_set<RankEnum> possible_start_ranks = {RankEnum::k3, RankEnum::kQ, RankEnum::kK, RankEnum::kA, RankEnum::k2};
    for (RankEnum rank : start_ranks_) {
        if (possible_start_ranks.find(rank) != possible_start_ranks.end())
            return true;
    }
    return false;
}

TurnMove SmallestFirstStraight::PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) {
    if (turn_info.should_contain_club_3) { 
        assert(Utility::ContainsClub3({rank_to_cards_->at(RankEnum::k3)[0].get_card()}) &&
                "You should have a club 3 if you want to play a Pair with club 3.");
        /*
            3-4-5-6-7 is better than 2-3-4-5-6 because it is smaller
            2-3-4-5-6 is better than A-2-3-4-5. Even though they are equally big (2 is the biggest card and 
                                straight compares the biggest card, 2-3-4-5-6 uses smaller cards, 
                                which is better for future plays)) 
        */
        std::vector<RankEnum> possible_start_ranks = {RankEnum::k3, RankEnum::k2, RankEnum::kA, RankEnum::kK, RankEnum::kQ};
        for (const auto& start_rank : possible_start_ranks) {
            if (std::find(start_ranks_.begin(), start_ranks_.end(), start_rank) != start_ranks_.end()) {
                auto cards_to_play = GetCardsToPlay(start_rank);
                return Utility::DrawCardsAndPlay(player, cards_to_play);
            }
        }
    }

    // has no top play, so can play any straight
    if (turn_info.top_play->get_card_pattern_name() == NullPattern::kNullPattern) {
        auto cards_to_play = GetCardsToPlay(start_ranks_[0]);
        return Utility::DrawCardsAndPlay(player, cards_to_play);
    }

    // Has top play, so need to play a straight bigger than it
    std::optional<Card> top_play_representative = turn_info.top_play->GetRepresentiveCard();
    assert(top_play_representative.has_value() && "Top play should have a representative card.");

    auto start_rank_and_representative = GetStartRankAndRepresentativeCardIfPossible(*top_play_representative);
    if (start_rank_and_representative.has_value()) {
        auto cards_to_play = GetCardsToPlay(start_rank_and_representative->first, 
                                            start_rank_and_representative->second);
        return Utility::DrawCardsAndPlay(player, cards_to_play);
    }
    return TurnMove::Pass(player);
    
}

std::vector<Utility::CardIndex> SmallestFirstStraight::GetCardsToPlay(RankEnum start_rank, 
                                                        std::optional<Utility::CardIndex> representative_card) {
    int start_rank_int = static_cast<int>(start_rank);
    std::vector<RankEnum> ranks_to_play = {static_cast<RankEnum>(start_rank_int), 
                                           static_cast<RankEnum>((start_rank_int + 1) % kTotalRankCount),
                                           static_cast<RankEnum>((start_rank_int + 2) % kTotalRankCount), 
                                           static_cast<RankEnum>((start_rank_int + 3) % kTotalRankCount), 
                                           static_cast<RankEnum>((start_rank_int + 4) % kTotalRankCount)};
    std::sort(ranks_to_play.begin(), ranks_to_play.end());

    std::vector<Utility::CardIndex> cards_to_play;
    for (const auto& rank : ranks_to_play) {
        if (representative_card.has_value() && rank == representative_card->get_card().get_rank())
            cards_to_play.push_back(*representative_card);
        else
            cards_to_play.push_back(rank_to_cards_->at(rank)[0]);
    }
    return cards_to_play;
}


std::optional<std::pair<RankEnum, Utility::CardIndex>> SmallestFirstStraight::GetStartRankAndRepresentativeCardIfPossible (
                                                                            Card top_play_representative) {

    for (RankEnum start_rank : start_ranks_) {
        RankEnum representative_rank = GetRepresentativeRank(start_rank);
        if (representative_rank == top_play_representative.get_rank()) {
            for (Utility::CardIndex card : rank_to_cards_->at(representative_rank)) {
                if (top_play_representative < card.get_card())
                    return std::make_pair(start_rank, card);
            }
        } else if (representative_rank < top_play_representative.get_rank().get()) {
            return std::make_pair(start_rank, rank_to_cards_->at(representative_rank)[0]);
        }
    }
    return std::nullopt;
}

void SmallestFirstStraight::GetStartRanksForStraight() {
    std::vector<int> ranks_has_at_least_one_card;
    for (const auto& rank_cards: *rank_to_cards_) {
        ranks_has_at_least_one_card.push_back(static_cast<int>(rank_cards.first));
        ranks_has_at_least_one_card.push_back(static_cast<int>(rank_cards.first) + kTotalRankCount); // circular straight
    }
    std::sort(ranks_has_at_least_one_card.begin(), ranks_has_at_least_one_card.end());
    
    std::deque<int> near_by_ranks;
    for (int rank : ranks_has_at_least_one_card) {
        near_by_ranks.push_back(rank);
        while (near_by_ranks.front() < rank - 4) 
            near_by_ranks.pop_front();
        
        if (near_by_ranks.size() == 5 && near_by_ranks.front() < kTotalRankCount)
            start_ranks_.push_back(static_cast<RankEnum>(near_by_ranks.front()));
    }    
}

void SmallestFirstStraight::Preprocess(
        std::shared_ptr<std::map<RankEnum, std::vector<Utility::CardIndex>>> rank_to_cards) {
    PlayStrategy::Preprocess(rank_to_cards);

    GetStartRanksForStraight();
    std::sort(start_ranks_.begin(), start_ranks_.end());
}

void SmallestFirstStraight::Reset() {
    PlayStrategy::Reset();
    start_ranks_.clear();
}