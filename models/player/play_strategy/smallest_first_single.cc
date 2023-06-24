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

TurnMove SmallestFirstSingle::PlayMatched(const TurnInfo& turn_info, std::shared_ptr<Player> player) {
    // std::map is sorted by key, so rank_to_cards_->begin() is the smallest rank
    // rank_to_cards_->begin()->second is the vector of cards with the smallest rank
    if (turn_info.is_first_play_in_each_round) {
        const auto& smallest_cards = rank_to_cards_->begin()->second;
        const auto& smallest_card = smallest_cards.at(0);
        Card card_to_play = *(player->get_hand()->DrawCard(smallest_card.get_index()));

        if (turn_info.should_contain_club_3)
            assert(Utility::ContainsClub3(std::vector<Card>{card_to_play}) && "The first play in the game should be club 3.");

        return TurnMove::Play(player, std::vector<Card>{card_to_play});
    } else {
        Card top_card = turn_info.top_play->GetRepresentiveCard().value();
        auto curr_card_index = GetFirstLargerCardIndex(top_card);
        if (curr_card_index.has_value()) {
            return Utility::DrawCardsAndPlay(player, {*curr_card_index});
        } else {
            return TurnMove::Pass(player);
        }
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
