#pragma once

#include <memory>
#include <vector>

#include "card/card.h"

class Deck {
public:
    Deck() = default;
    void Shuffle();
    std::shared_ptr<const Card> DrawOneCard();
    void PutCard(std::shared_ptr<const Card> card);
    int size() const;

private:
    std::vector<std::shared_ptr<const Card>> cards_;
};