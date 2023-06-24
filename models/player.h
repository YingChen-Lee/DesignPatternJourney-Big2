#pragma once

#include "card/card.h"
#include "hand.h"
#include "turn_move.h"
#include "turn_info.h"

#include <memory>
#include <string>
#include <vector>

class TurnMove;
class Player {
public:
    Player() = default;
    virtual void NameSelf() = 0;
    std::string get_name() const { return name_; }

    void AddCardToHand(std::shared_ptr<const Card> card);
    bool HasClub3() const;
    int GetHandSize() const ;
    std::shared_ptr<Hand> get_hand() const { return hand_; }
    
    virtual TurnMove play(const TurnInfo& turn_info) = 0;

    void ResetData();
    
protected:
    std::string name_;
    std::shared_ptr<Hand> hand_ = std::make_shared<Hand>();
};
