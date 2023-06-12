#pragma once

#include "card/card.h"
#include "card_pattern/card_pattern.h"
#include "hand.h"

#include "commandline_interface/input_interface.h"

#include <memory>
#include <string>

class Player {
public:
    /*
    std::shared_ptr<const Card> ShowCard(std::shared_ptr<ShowCardContext> context);
    void AddCardToHand(std::shared_ptr<const Card> card);
    int GetHandSize() const ;
    void ResetData();
    void set_strategy(std::shared_ptr<ShowCardStrategy> strategy) {strategy_ = strategy;}
    */
    void NameSelf(InputInterface& input_interface);
    std::string get_name() const { return name_; }

private:
    std::string name_;
    /*
    std::shared_ptr<Hand> hand_ = std::make_shared<Hand>();
    std::shared_ptr<ShowCardStrategy> strategy_;
    int point_;
    */
};
