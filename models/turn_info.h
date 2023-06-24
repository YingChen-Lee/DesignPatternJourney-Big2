#pragma once

#include <memory>

#include "card_pattern/card_pattern.h"

class TurnInfo {
public:
    TurnInfo(bool should_contain_club_3, 
             bool is_first_play_in_each_round, 
             const std::shared_ptr<CardPattern> top_play) :
                should_contain_club_3(should_contain_club_3), 
                is_first_play_in_each_round(is_first_play_in_each_round), 
                top_play(top_play) {}
                
    const bool should_contain_club_3;
    const bool is_first_play_in_each_round;
    const std::shared_ptr<CardPattern> top_play;
};