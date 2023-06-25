#include "smallest_first_single.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
#include <optional>
#include <utility>

#include "strategy_utility.h"

bool SmallestFirstSingle::HasValidPlayForThisPattern() {
    return true;
}

bool SmallestFirstSingle::CanPlayWithClub3() {
    return true;
}

TurnMove SmallestFirstSingle::PlayWithClub3(std::shared_ptr<Player> player) {
    return PlaySmallestCard(player, true);
}

TurnMove SmallestFirstSingle::PlaySmallest(std::shared_ptr<Player> player) {
    return PlaySmallestCard(player, false);
}

TurnMove SmallestFirstSingle::PlaySmallestCard(std::shared_ptr<Player> player, bool should_contain_club_3) {
    // std::map is sorted by key, so rank_to_cards_->begin() is the smallest rank
    // rank_to_cards_->begin()->second is the vector of cards with the smallest rank
    const auto& smallest_cards = rank_to_cards_->begin()->second;
    const auto& smallest_card = smallest_cards.at(0);
    if (should_contain_club_3)
        assert(Utility::ContainsClub3({smallest_card}) && "The first play in the game should be club 3.");
    return Utility::DrawCardsAndPlay(player, {smallest_card});
}

TurnMove SmallestFirstSingle::PlayBiggerThanTopPlayOrPass(std::shared_ptr<Player> player, const std::shared_ptr<CardPattern> top_play) {
    Card top_card = top_play->GetRepresentiveCard().value();
    auto curr_card_index = GetFirstLargerCardIndex(top_card);
    if (curr_card_index.has_value()) {
        return Utility::DrawCardsAndPlay(player, {*curr_card_index});
    } else {
        return TurnMove::Pass(player);
    }
}

std::optional<Utility::CardIndex> SmallestFirstSingle::GetFirstLargerCardIndex(const Card& top_card) {
    for (auto& curr_cards : *rank_to_cards_) {
        for (auto& curr_card_index : curr_cards.second) {
            if (top_card < curr_card_index.get_card())
                return curr_card_index;
        }
    }
    return std::nullopt;
}
