#include "ai_player.h"

#include <algorithm>
#include <bits/stdc++.h>

#include "../hand.h"

void AiPlayer::NameSelf() {
    int name_int = rand() % 1000;
    name_ = "AI_" + (name_ == "" ? std::to_string(name_int) : name_);
}

TurnMove AiPlayer::play(const TurnInfo& turn_info) {
    auto rank_to_cards = Utility::GetRankCardsMap(hand_->get_cards());

    return play_strategy_->Play(turn_info, std::make_shared<AiPlayer>(*this), rank_to_cards);
}