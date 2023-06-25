#include "output_interface.h"

#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>
#include <memory>
#include <sstream>

#include "../models/card_pattern/null_pattern.h"
#include "../models/card_pattern/single.h"
#include "../models/card_pattern/pair.h"
#include "../models/card_pattern/straight.h"
#include "../models/card_pattern/full_house.h"

/*
const std::unordered_map<SuitEnum, std::string> OutputInterface::suit_enum_to_string = {
    {SuitEnum::kSpade, "S"}, {SuitEnum::kHeart, "H"}, {SuitEnum::kDiamond, "D"},
    {SuitEnum::kClub, "C"}
};
*/
//TTTIIIMMM, prettier
const std::unordered_map<SuitEnum, std::string> OutputInterface::suit_enum_to_string = {
    {SuitEnum::kSpade, "♠"}, {SuitEnum::kHeart, "♥"}, {SuitEnum::kDiamond, "♦"},
    {SuitEnum::kClub, "♣"}
};

OutputInterface::OutputInterface(const std::string& filepath) : filepath_(filepath) {
    OpenFile();
}

OutputInterface::~OutputInterface() {
    CloseFile();
}

void OutputInterface::OpenFile() {
    file_.open(filepath_);
    assert(file_.is_open() && "File not found");
}

void OutputInterface::CloseFile() {
    file_.close();
}

void OutputInterface::OutputMessage(const std::string& message) {
    file_ << message;
    std::cout << message;
}

void OutputInterface::OutputStartNewRound() { 
    OutputMessage("\n\n新的回合開始了。\n"); //TTTIIIMMM, prettier
    // OutputMessage("新的回合開始了。\n");
}

void OutputInterface::OutputPlayerTurn(const std::string& player_name) {
    OutputMessage(std::format("\n輪到{}了\n", player_name)); //TTTIIIMMM, prettier
    // OutputMessage(std::format("輪到{}了\n", player_name));
}

void OutputInterface::OutputHand(const Hand& hand){
    auto cards = hand.get_cards();
    std::vector<std::string> card_strings;
    for (const auto& card : cards)
        card_strings.push_back(CardToString(*card));
    
    for (int i = 0; i < card_strings.size(); i++) {
        std::string index_string = std::to_string(i);
        std::string space = (i != card_strings.size() - 1) ? 
                             std::string(card_strings[i].size() + 1 - 2 - index_string.size(), ' ') : //TTTIIIMMM, prettier
                            //  std::string(card_strings[i].size() + 1 - index_string.size(), ' ') : 
                             "";
        OutputMessage(index_string + space);
    }
    OutputMessage("   -1"); //TTTIIIMMM, prettier
    OutputMessage("\n");
    for (int i = 0; i < card_strings.size(); i++) {
        std::string card_string = card_strings[i];
        std::string space = (i != card_strings.size() - 1) ? 
                             " ":
                             "";
        OutputMessage(card_string + space);
    }
    OutputMessage(" PASS"); //TTTIIIMMM, prettier
    OutputMessage("\n");
}

void OutputInterface::OutputCards(const std::vector<Card>& cards) {
    std::vector<Card> sorted_cards(cards);
    std::sort(sorted_cards.begin(), sorted_cards.end());

    std::vector<std::string> card_strings;
    for (const auto& card : sorted_cards)
        card_strings.push_back(CardToString(card));
    
    for (int i = 0; i < card_strings.size(); i++) {
        std::string card_string = card_strings[i];
        std::string space = (i != card_strings.size() - 1) ? 
                             " ":
                             "";
        OutputMessage(card_string + space);
    }
    OutputMessage("\n");
}

std::string OutputInterface::CardToString(const Card& card) const {
    std::string card_string = std::format("{}[{}]", 
                                          suit_enum_to_string.at(card.get_suit().get()), 
                                          card.get_rank().ToString());
    return card_string;
}

void OutputInterface::OutputPass(const std::string& player_name, bool is_valid) {
    if (is_valid)
        OutputMessage(std::format("玩家 {} PASS.\n", player_name));
    else
        OutputMessage("你不能在新的回合中喊 PASS\n");
}

void OutputInterface::OutputPlay(const std::string& player_name, const std::vector<Card>& cards,
                                 const std::string& card_pattern_name) {
    std::string card_pattern_name_to_show = "";
    if (card_pattern_name == Single::kSingle)
        card_pattern_name_to_show = "單張";
    else if (card_pattern_name == Pair::kPair)
        card_pattern_name_to_show = "對子";
    else if (card_pattern_name == Straight::kStraight)
        card_pattern_name_to_show = "順子";
    else if (card_pattern_name == FullHouse::kFullHouse)
        card_pattern_name_to_show = "葫蘆";
    else
        assert(false && "Card pattern name is not valid, Cannot output!");

    OutputMessage(std::format("玩家 {} 打出了 {} ", player_name, card_pattern_name_to_show));
    OutputCards(cards);
}

void OutputInterface::OutputInvalidPlay(const std::string& player_name) {
    OutputMessage("此牌型不合法，請再嘗試一次。\n");
}

void OutputInterface::OutputWinner(const std::string& player_name) {
    OutputMessage(std::format("遊戲結束，遊戲的勝利者為 {}\n", player_name));
}