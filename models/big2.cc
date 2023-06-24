#include "big2.h"

#include <cassert>

#include "turn_info.h"
#include "card_pattern/null_pattern.h"

//TTTIIIMMM
#include <iostream>

namespace {
bool ContainsClub3(const std::vector<Card>& cards) {
    for (const auto& card : cards) {
        if (card.get_suit().get() == SuitEnum::kClub && card.get_rank().get() == RankEnum::k3)
            return true;
    }
    return false;
}
}  // namespace

Big2::Big2(std::shared_ptr<InputInterface> input_interface, std::shared_ptr<OutputInterface> output_interface,
           const std::shared_ptr<CardPatternParser>& card_pattern_parser) :
        input_interface_(input_interface),
        output_interface_(output_interface),
        card_pattern_parser_(card_pattern_parser) {
    top_play_ = std::make_shared<NullPattern>();
}

void Big2::Start() {
    for (auto& player : players_)
        player->NameSelf();
        
    InitDeck();
    DealCardsToPlayers();

    while (!HasWinner())
        StartNewRound();

    output_interface_->OutputWinner(winner_->get_name());
}

void Big2::AddPlayer(std::shared_ptr<Player> player) {
    players_.push_back(player);
}

void Big2::InitDeck() {
    deck_ = input_interface_->GetDeck();
}

void Big2::DealCardsToPlayers() {
    for (int i = 0; i < 13; i++) {
        for (auto& player : players_)
            player->AddCardToHand(deck_.DrawOneCard());
    }
    assert(deck_.size() == 0 && "Deck size is not 0 after deal all cards");
}

bool Big2::HasWinner() const {
    return winner_ != nullptr;
}

void Big2::StartNewRound() {
    curr_round_++;
    output_interface_->OutputStartNewRound();

    int curr_player_index = GetFirstPlayerIndex();
    top_player_index_ = -1;
    top_play_ = std::make_shared<NullPattern>();

    while (curr_player_index != top_player_index_) {
        auto curr_player = players_[curr_player_index];
        output_interface_->OutputPlayerTurn(curr_player->get_name());

        CurrPlayerPlaysUntilValid(curr_player_index);
        
        if (curr_player->GetHandSize() == 0) {
            winner_ = curr_player;
            break;
        }
    
        curr_player_index = (curr_player_index + 1) % players_.size();
    }
}

int Big2::GetFirstPlayerIndex() const {
    if (curr_round_ != 1)
        return top_player_index_;

    for (int i = 0; i < players_.size(); i++) {
        if (players_[i]->HasClub3())
            return i;
    }
    assert(false && "No player has Club 3");
    return -1;
}

void Big2::CurrPlayerPlaysUntilValid(int curr_player_index){
    std::shared_ptr<Player> curr_player = players_[curr_player_index];

    bool is_first_play_in_each_round = (top_player_index_ == -1);
    bool should_contain_club_3 = (curr_round_ == 1 && is_first_play_in_each_round);

    TurnInfo info_for_player(should_contain_club_3, is_first_play_in_each_round, top_play_);

    bool has_played_valid_move = false;
    while (!has_played_valid_move) {
        output_interface_->OutputHand(*(curr_player->get_hand()));

        TurnMove turn_move = curr_player->play(info_for_player);
        turn_move.AddParsedCardPattern(ParseCardPattern(turn_move.get_cards()));
        
        has_played_valid_move = IsValidPlay(turn_move);
        if (has_played_valid_move && !turn_move.IsPass()) {
            top_player_index_ = curr_player_index;
            top_play_ = turn_move.get_card_pattern();
        }
        
        if (!has_played_valid_move)
            turn_move.Undo();

        PrintMoveResult(turn_move, has_played_valid_move);
    }
}

bool Big2::IsValidPlay(const TurnMove& turn_move) const {
    bool is_first_play_in_each_round = (top_player_index_ == -1);
    bool should_contain_club_3 = (curr_round_ == 1 && is_first_play_in_each_round);
    if (turn_move.IsPass()) {
        return !is_first_play_in_each_round;
    } else {
        if (turn_move.get_card_pattern()->get_card_pattern_name() == NullPattern::kNullPattern) {
            return false;
        } else if (should_contain_club_3) {
            return ContainsClub3(turn_move.get_cards());
        } else if (is_first_play_in_each_round) {
            return true;
        } else {
            return turn_move.get_card_pattern()->IsBigger(top_play_);
        }
    }
}

void Big2::PrintMoveResult(const TurnMove& turn_move, bool is_valid_move) const {
    std::string player_name = turn_move.get_player()->get_name();
    if (is_valid_move) {
        if (turn_move.IsPass())
            output_interface_->OutputPass(player_name, true);
        else
            output_interface_->OutputPlay(player_name, turn_move.get_cards(), 
                                         turn_move.get_card_pattern()->get_card_pattern_name());
    } else {
        if (turn_move.IsPass())
            output_interface_->OutputPass(player_name, false);
        else
            output_interface_->OutputInvalidPlay(player_name);
    }
}

std::shared_ptr<CardPattern> Big2::ParseCardPattern(const std::vector<Card>& cards) const {
    assert(card_pattern_parser_ != nullptr && "card_pattern_parser_ is nullptr");
    return card_pattern_parser_->Parse(cards);
}