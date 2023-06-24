#include "strategy_utility.h"

#include <algorithm>
#include <memory>
#include <map>
#include <utility>
#include <vector>

#include "../../card/card.h"
#include "../../card/rank.h"

namespace Utility {

bool ContainsClub3(const std::vector<Card>& cards) {
    for (const auto& card : cards) {
        if (card.get_suit().get() == SuitEnum::kClub && card.get_rank().get() == RankEnum::k3)
            return true;
    }
    return false;
}

/**
  return a map from RankEnum to a vector of cards with that rank, also the index in the origin vector
  e.g. cards = [heart3, heart4, club4, spade4, club3...]
         map = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                 RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                 ...]}
  
  Note that the order of the cards in the vector is sorted
*/
std::map<RankEnum, std::vector<CardIndex>> GetRankCardsMap(const std::vector<std::shared_ptr<const Card>>& cards) {
    std::map<RankEnum, std::vector<CardIndex>> rank_to_cards;
    for (int i = 0; i < cards.size(); i++) {
        Card curr_card = *(cards[i]);
        rank_to_cards[curr_card.get_rank().get()].push_back(CardIndex(curr_card, i));
    }
    for (auto& rank_cards : rank_to_cards) {
        std::sort(rank_cards.second.begin(), rank_cards.second.end());
    }
    return rank_to_cards;
}

TurnMove DrawCardsAndPlay(std::shared_ptr<Player> player, 
                          const std::vector<Utility::CardIndex>& card_indices) {
    std::vector<int> index_to_draw(card_indices.size());
    
    std::transform(card_indices.begin(), card_indices.end(), index_to_draw.begin(), 
                   [](const CardIndex& card_index) { return card_index.get_index(); });
    // Need to draw the index reversely to avoid larger index changed by remove
    std::sort(index_to_draw.rbegin(), index_to_draw.rend());

    std::vector<Card> cards_to_play;
    for (const auto& index : index_to_draw)
        cards_to_play.push_back( *(player->get_hand()->DrawCard(index)) );

    return TurnMove::Play(player, cards_to_play);
}

}  // namespace Utility