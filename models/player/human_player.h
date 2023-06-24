#pragma once

#include "../player.h"

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
class HumanPlayer : public Player {
public:
    HumanPlayer(std::shared_ptr<InputInterface> input_interface) : input_interface_(input_interface) {}
    virtual void NameSelf() override;
    
    virtual TurnMove play(const TurnInfo& turn_info) override;

private:
    std::shared_ptr<InputInterface> input_interface_;
};
