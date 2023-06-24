#include "player.h"

#include "hand.h"

void Player::AddCardToHand(std::shared_ptr<const Card> card) {
    hand_->AddCard(card);
}

bool Player::HasClub3() const {
    return hand_->HasClub3();
}

int Player::GetHandSize() const {
    return hand_->get_size();
}

void Player::ResetData() {
    hand_->Reset();
    name_ = "";
}
