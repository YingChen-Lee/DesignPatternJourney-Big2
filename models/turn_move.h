#pragma once

#include <memory>
#include <vector>

#include "card/card.h"
#include "card_pattern/card_pattern.h"
#include "player.h"

class Player;

class TurnMove {
public:
    static TurnMove Pass(const std::shared_ptr<Player> player);
    static TurnMove Play(const std::shared_ptr<Player> player, std::vector<Card> cards);
    
    TurnMove(const std::shared_ptr<Player> player, bool pass, std::vector<Card> cards) :
        player_(player),
        pass_(pass),
        cards_(cards) {}

    bool IsPass() const { return pass_; }
    std::vector<Card> get_cards() const { return cards_; }
    void Undo();
    
    void AddParsedCardPattern(std::shared_ptr<CardPattern> card_pattern) { card_pattern_ = card_pattern; }
    std::shared_ptr<CardPattern> get_card_pattern() const { return card_pattern_; }
    
    std::shared_ptr<Player> get_player() const { return player_; }

private:
    const std::shared_ptr<Player> player_;
    const bool pass_; 
    const std::vector<Card> cards_;
    std::shared_ptr<CardPattern> card_pattern_;
};