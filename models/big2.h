#pragma once

#include <memory>
#include <vector>

#include "../io_interface/input_interface.h"
#include "../io_interface/output_interface.h"
#include "card_pattern/card_pattern.h"
#include "card_pattern_parser/card_pattern_parser.h"
#include "card_pattern_parser/null_parser.h"
#include "player.h"

class Big2 {
public:
    Big2(std::shared_ptr<InputInterface> input_interface, std::shared_ptr<OutputInterface> output_interface, 
         const std::shared_ptr<CardPatternParser>& card_pattern_parser);
    
    void AddPlayer(std::shared_ptr<Player> player);
    void Start();

private:
    void DealCardsToPlayers();
    void InitDeck();
    bool HasWinner() const ;
    void StartNewRound();
    int GetFirstPlayerIndex() const ;
    void CurrPlayerPlaysUntilValid(int curr_player_index);
    bool IsValidPlay(const TurnMove& turn_move) const ;
    void PrintMoveResult(const TurnMove& turn_move, bool is_valid_move) const ;
    
    std::shared_ptr<CardPattern> ParseCardPattern(const std::vector<Card>& cards) const;

    int top_player_index_ = -1;
    std::shared_ptr<CardPattern> top_play_ = nullptr;
    int curr_round_ = 0;
    std::shared_ptr<Player> winner_ = nullptr;

    std::vector<std::shared_ptr<Player>> players_;
    Deck deck_;

    std::shared_ptr<InputInterface> input_interface_;
    std::shared_ptr<OutputInterface> output_interface_;
    
    std::shared_ptr<CardPatternParser> card_pattern_parser_ = nullptr;
};