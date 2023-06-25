#pragma once

#include <algorithm>
#include <memory>
#include <map>
#include <utility>
#include <vector>

#include "../../card/card.h"
#include "../../card/rank.h"
#include "../../turn_move.h"

namespace Utility {

class CardIndex {
public:
    CardIndex(Card card, int index) : card_(card), index_(index) {}
    Card get_card() const { return card_; }
    int get_index() const { return index_; }
    bool operator<(const CardIndex& other) const {
        return card_ < other.card_;
    }
private:
    Card card_;
    int index_;
};

bool ContainsClub3(const std::vector<CardIndex>& cards);

/**
  return a map from RankEnum to a vector of cards with that rank, also the index in the origin vector
  e.g. cards = [heart3, heart4, club4, spade4, club3...]
         map = { RankEnum::k3 : [(club3, 4), (heart3, 0)], 
                 RankEnum::k4 : [(club4, 2), (heart4, 1), (spade4, 3)], 
                 ...]}
  
  Note that the order of the cards in the vector is sorted
*/
std::shared_ptr<std::map<RankEnum, std::vector<CardIndex>>> GetRankCardsMap(const std::vector<std::shared_ptr<const Card>>& cards);

TurnMove DrawCardsAndPlay(std::shared_ptr<Player> player, const std::vector<Utility::CardIndex>& card_indices);
}  // namespace Utility