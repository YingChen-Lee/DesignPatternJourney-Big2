#include "turn_move.h"

TurnMove TurnMove::Pass(const std::shared_ptr<Player> player) {
    return TurnMove(player, true, std::vector<Card>());
}

TurnMove TurnMove::Play(const std::shared_ptr<Player> player, 
                        std::vector<Card> cards) {
    return TurnMove(player, false, cards);
}

void TurnMove::Undo() {
    for (const Card& card : cards_)
        player_->AddCardToHand(std::make_shared<const Card>(card));
}
