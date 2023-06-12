#include "input_interface.h"

#include <cassert>
#include <memory>
#include <sstream>

namespace {
std::istringstream GetNextLineIstringStream(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    return std::istringstream(line);
}
}  // namespace

const std::unordered_map<std::string, SuitEnum> InputInterface::string_to_suit_enum = {
    {"C", SuitEnum::kClub}, {"D", SuitEnum::kDiamond}, {"H", SuitEnum::kHeart},
    {"S", SuitEnum::kSpade}
};

const std::unordered_map<std::string, RankEnum> InputInterface::string_to_rank_enum = {
    {"3", RankEnum::k3}, {"4", RankEnum::k4}, {"5", RankEnum::k5}, {"6", RankEnum::k6}, 
    {"7", RankEnum::k7}, {"8", RankEnum::k8}, {"9", RankEnum::k9}, {"10", RankEnum::k10}, 
    {"J", RankEnum::kJ}, {"Q", RankEnum::kQ}, {"K", RankEnum::kK}, {"A", RankEnum::kA},
    {"2", RankEnum::k2}
};

InputInterface::InputInterface(const std::string& filepath) : filepath_(filepath) {
    OpenFile();
}

InputInterface::~InputInterface() {
    CloseFile();
}

void InputInterface::OpenFile() {
    file_.open(filepath_);
    assert(file_.is_open() && "File not found");
}

void InputInterface::CloseFile() {
    file_.close();
}

Deck InputInterface::GetDeck() {
    assert(file_.is_open() && "File not found");

    Deck deck;
    std::istringstream iss = GetNextLineIstringStream(file_);
    std::string card_string;
    while (iss >> card_string)
        deck.PutCard(std::make_shared<const Card>(GetCard(card_string)));

    assert(deck.size() == 52 && "Deck size is not 52");
    return deck;
}

std::vector<std::string> InputInterface::GetPlayersName() {
    assert(file_.is_open() && "File not found");
    std::vector<std::string> players_name;
    for (int i = 0; i < 4; i++) {
        std::string line;
        std::getline(file_, line);
        players_name.push_back(line);
    }
    return players_name;
}

std::vector<int> InputInterface::GetNextPlayIndices() {
    assert(file_.is_open() && "File not found");

    std::vector<int> play_indices;
    std::istringstream iss = GetNextLineIstringStream(file_);
    std::string index_string;
    while (iss >> index_string)
        play_indices.push_back(std::stoi(index_string));

    assert(!play_indices.empty() && "No play indices");
    return play_indices;
}

Card InputInterface::GetCard(const std::string& card_string) {
    assert(file_.is_open() && "File not found");

    SuitEnum suit = InputInterface::string_to_suit_enum.at(card_string.substr(0, 1));
    int end_index = card_string.find("]");
    // 0 1 2 3 4
    // A [ 1 0 ]   => end_index = 4
    RankEnum rank = InputInterface::string_to_rank_enum.at(card_string.substr(2, end_index - 2));
    return Card(Suit(suit), Rank(rank));
}
