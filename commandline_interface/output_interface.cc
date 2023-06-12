#include "output_interface.h"

#include <cassert>
#include <format>
#include <iostream>
#include <memory>
#include <sstream>

const std::unordered_map<SuitEnum, std::string> OutputInterface::suit_enum_to_string = {
    {SuitEnum::kSpade, "S"}, {SuitEnum::kHeart, "H"}, {SuitEnum::kDiamond, "D"},
    {SuitEnum::kClub, "C"}
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

void OutputInterface::OutputHand(const Hand& hand) {
    auto cards = hand.get_cards();
    std::vector<std::string> card_strings;
    for (const auto& card : cards)
        card_strings.push_back(CardToString(*card));
    
    for (int i = 0; i < card_strings.size(); i++) {
        std::string index_string = std::to_string(i);
        std::string space = (i != card_strings.size() - 1) ? 
                             std::string(card_strings[i].size() + 1 - index_string.size(), ' ') : 
                             "";
        OutputMessage(index_string + space);
    }
    OutputMessage("\n");
    for (int i = 0; i < card_strings.size(); i++) {
        std::string card_string = card_strings[i];
        std::string space = (i != card_strings.size() - 1) ? 
                             " ":
                             "";
        OutputMessage(card_string + space);
    }
    OutputMessage("\n");
}

void OutputInterface::OutputCards(const std::vector<std::shared_ptr<const Card>>& cards) {
    std::vector<std::string> card_strings;
    for (const auto& card : cards)
        card_strings.push_back(CardToString(*card));
    
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
