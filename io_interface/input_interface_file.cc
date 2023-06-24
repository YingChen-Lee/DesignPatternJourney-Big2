#include "input_interface_file.h"

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

const std::unordered_map<std::string, SuitEnum> InputInterfaceFile::string_to_suit_enum = {
    {"C", SuitEnum::kClub}, {"D", SuitEnum::kDiamond}, {"H", SuitEnum::kHeart},
    {"S", SuitEnum::kSpade}
};

const std::unordered_map<std::string, RankEnum> InputInterfaceFile::string_to_rank_enum = {
    {"3", RankEnum::k3}, {"4", RankEnum::k4}, {"5", RankEnum::k5}, {"6", RankEnum::k6}, 
    {"7", RankEnum::k7}, {"8", RankEnum::k8}, {"9", RankEnum::k9}, {"10", RankEnum::k10}, 
    {"J", RankEnum::kJ}, {"Q", RankEnum::kQ}, {"K", RankEnum::kK}, {"A", RankEnum::kA},
    {"2", RankEnum::k2}
};

InputInterfaceFile::InputInterfaceFile(const std::string& filepath) : filepath_(filepath) {
    OpenFile();
    GetDeckFromFile();
    GetPlayersNameFromFile();
    GetPlayIndicesFromFile();
    CloseFile();
}

void InputInterfaceFile::OpenFile() {
    file_.open(filepath_);
    assert(file_.is_open() && "File not found");
}

void InputInterfaceFile::CloseFile() {
    file_.close();
}

void InputInterfaceFile::GetDeckFromFile() {
    assert(file_.is_open() && "File not found");

    std::istringstream iss = GetNextLineIstringStream(file_);
    std::string card_string;
    while (iss >> card_string)
        deck_.PutCard(std::make_shared<const Card>(GetCard(card_string)));

    assert(deck_.size() == 52 && "Deck size is not 52");
}

void InputInterfaceFile::GetPlayersNameFromFile() {
    assert(file_.is_open() && "File not found");

    for (int i = 0; i < 4; i++) {
        std::string line;
        std::getline(file_, line);
        players_name_.push_back(line);
    }
}

void InputInterfaceFile::GetPlayIndicesFromFile() {
    assert(file_.is_open() && "File not found");

    std::string line;
    while (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::vector<int> play_indices;
        std::string index_string;
        while (iss >> index_string)
            play_indices.push_back(std::stoi(index_string));
        play_indices_.push_back(play_indices);
    }
}

Deck InputInterfaceFile::GetDeck() {
    return deck_;
}

std::string InputInterfaceFile::GetNextPlayerName() {
    assert(players_name_.size() > 0 && "No player name");
    std::string player_name = players_name_.front();
    players_name_.pop_front();
    return player_name;
}

std::vector<int> InputInterfaceFile::GetNextPlayIndices() {
    assert(play_indices_.size() > 0 && "No play indices");
    std::vector<int> play_indices = play_indices_.front();
    play_indices_.pop_front();
    return play_indices;
}

Card InputInterfaceFile::GetCard(const std::string& card_string) {
    assert(file_.is_open() && "File not found");

    SuitEnum suit = InputInterfaceFile::string_to_suit_enum.at(card_string.substr(0, 1));
    int end_index = card_string.find("]");
    // 0 1 2 3 4
    // A [ 1 0 ]   => end_index = 4
    RankEnum rank = InputInterfaceFile::string_to_rank_enum.at(card_string.substr(2, end_index - 2));
    return Card(Suit(suit), Rank(rank));
}
