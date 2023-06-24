#pragma once

#include "../player.h"
#include "play_strategy/play_strategy.h"
#include "play_strategy/strategy_utility.h"

#include "../card/card.h"
#include "../card_pattern/card_pattern.h"
#include "../hand.h"
#include "../turn_move.h"
#include "../turn_info.h"

#include "../../io_interface/input_interface.h"

#include <memory>
#include <string>
#include <vector>

class TurnMove;
class AiPlayer : public Player {
public:
    AiPlayer(std::shared_ptr<PlayStrategy> play_strategy) : play_strategy_(play_strategy) {}
    AiPlayer(std::shared_ptr<PlayStrategy> play_strategy, const std::string& name) : play_strategy_(play_strategy) {
        name_ = name;
    }
    
    virtual void NameSelf() override;
    
    virtual TurnMove play(const TurnInfo& turn_info) override;

private:
    std::shared_ptr<PlayStrategy> play_strategy_;
};
