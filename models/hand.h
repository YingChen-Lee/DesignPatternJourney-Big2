#pragma once

#include <memory>
#include <vector>

#include "card/card.h"

class Hand {
public:
    Hand() = default;
    void AddCard(std::shared_ptr<const Card> card);
    std::vector<std::shared_ptr<const Card>> get_cards() const;
    std::shared_ptr<const Card> DrawCard(int index);
    int get_size() const;
    void Reset();
    bool HasClub3() const;
    void Sort();

private:
    std::vector<std::shared_ptr<const Card>> cards_; 
};
