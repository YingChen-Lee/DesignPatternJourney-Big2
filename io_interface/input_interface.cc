#include "input_interface.h"

#include "../models/card/card.h"
#include "../models/card/suit.h"
#include "../models/card/rank.h"

Deck InputInterface::GetDeck() {
    Deck deck;
    for (int s = static_cast<int>(SuitEnum::kClub); s <= static_cast<int>(SuitEnum::kSpade); s++) {
        for (int r = static_cast<int>(RankEnum::k3); r <= static_cast<int>(RankEnum::k2); r++) {
            std::shared_ptr<const Card> new_card = 
                std::make_shared<const Card>(Suit(SuitEnum(s)), Rank(RankEnum(r)));
            deck.PutCard(new_card);
        }
    }
    deck.Shuffle();
    return deck;
}
