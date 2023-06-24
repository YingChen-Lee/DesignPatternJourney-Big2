#include "human_player.h"

#include <algorithm>
#include <bits/stdc++.h>

#include "../hand.h"

void HumanPlayer::NameSelf() {
    name_ = input_interface_->GetNextPlayerName();
}

TurnMove HumanPlayer::play(const TurnInfo& turn_info) {
    auto input_indices = input_interface_->GetNextPlayIndices();
    if (input_indices[0] == -1)
        return TurnMove::Pass(std::make_shared<HumanPlayer>(*this));
    
    std::sort(input_indices.rbegin(), input_indices.rend());
    std::vector<Card> cards_to_play;
    for (auto index : input_indices)
        cards_to_play.push_back(*(hand_->DrawCard(index)));
    
    return TurnMove::Play(std::make_shared<HumanPlayer>(*this), cards_to_play);
}