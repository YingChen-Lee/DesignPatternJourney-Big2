#include <iostream>
#include <cstdlib> // for time
#include <filesystem>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "models/big2.h"

#include "models/player.h"
#include "models/player/human_player.h"
#include "models/player/ai_player.h"
#include "models/player/play_strategy/play_strategy.h"
#include "models/player/play_strategy/null_strategy.h"
#include "models/player/play_strategy/smallest_first_single.h"
#include "models/player/play_strategy/smallest_first_pair.h"
#include "models/player/play_strategy/smallest_first_full_house.h"
#include "models/player/play_strategy/smallest_first_straight.h"

#include "io_interface/input_interface.h"
#include "io_interface/input_interface_file.h"
#include "io_interface/input_interface_terminal.h"
#include "io_interface/output_interface.h"

#include "card_pattern_parser/card_pattern_parser.h"
#include "card_pattern_parser/null_parser.h"
#include "card_pattern_parser/single_parser.h"
#include "card_pattern_parser/pair_parser.h"
#include "card_pattern_parser/straight_parser.h"
#include "card_pattern_parser/full_house_parser.h"

static const std::string kDirectoryName = "../測資集合/";

void PlayFromInputFiles(); 
std::vector<std::string> GetFileNames(const std::string& directory_path);

void PlayFromTerminalWithoutAi();

void PlayFromTerminalWithAi();

void AllAiPlay();

void RunNewGame(std::shared_ptr<InputInterface> input_interface, 
                std::shared_ptr<OutputInterface> output_interface,
                std::vector<std::shared_ptr<Player>> players);

int main() {
    srand((unsigned) time(NULL));
    
    // PlayFromInputFiles();

    // PlayFromTerminalWithoutAi();

    PlayFromTerminalWithAi();

    // AllAiPlay();
           
    return 0;
}

void PlayFromInputFiles() {
    std::vector<std::string> input_file_names = GetFileNames(kDirectoryName);
    for (const auto filename : input_file_names) {
        std::string input_file_name = kDirectoryName + filename + ".in";
        std::string output_file_name = kDirectoryName + "my_output/" + filename + ".test.out";
        std::shared_ptr<InputInterface> input_interface = std::make_shared<InputInterfaceFile>(input_file_name);
        std::shared_ptr<OutputInterface> output_interface = std::make_shared<OutputInterface>(output_file_name);
        
        std::shared_ptr<Player> player1 = std::make_shared<HumanPlayer>(input_interface);
        std::shared_ptr<Player> player2 = std::make_shared<HumanPlayer>(input_interface); 
        std::shared_ptr<Player> player3 = std::make_shared<HumanPlayer>(input_interface); 
        std::shared_ptr<Player> player4 = std::make_shared<HumanPlayer>(input_interface); 
        RunNewGame(input_interface, output_interface, {player1, player2, player3, player4});
    }
}

std::vector<std::string> GetFileNames(const std::string& directory_path) {
    std::vector<std::string> file_names;
    for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            std::filesystem::path filePath = entry.path();
            if (filePath.extension() == ".in")
                file_names.push_back(filePath.stem().string());
        }
    }
    return file_names;
}

void PlayFromTerminalWithoutAi() {
    std::string output_file_name = kDirectoryName + "my_output/" + "input_from_terminal_no_ai.test.out";
    std::shared_ptr<InputInterface> input_interface = std::make_shared<InputInterfaceTerminal>();
    std::shared_ptr<OutputInterface> output_interface = std::make_shared<OutputInterface>(output_file_name);

    std::shared_ptr<Player> player1 = std::make_shared<HumanPlayer>(input_interface); 
    std::shared_ptr<Player> player2 = std::make_shared<HumanPlayer>(input_interface); 
    std::shared_ptr<Player> player3 = std::make_shared<HumanPlayer>(input_interface); 
    std::shared_ptr<Player> player4 = std::make_shared<HumanPlayer>(input_interface); 
    
    RunNewGame(input_interface, output_interface, {player1, player2, player3, player4});
}

void PlayFromTerminalWithAi() {
    std::string output_file_name = kDirectoryName + "my_output/" + "input_from_terminal_ai.test.out";
    std::shared_ptr<InputInterface> input_interface = std::make_shared<InputInterfaceTerminal>();
    std::shared_ptr<OutputInterface> output_interface = std::make_shared<OutputInterface>(output_file_name);

    std::shared_ptr<Player> player1 = std::make_shared<AiPlayer>(std::make_shared<SmallestFirstStraight>(
                                                                 std::make_shared<SmallestFirstFullHouse>(
                                                                 std::make_shared<SmallestFirstPair>(
                                                                 std::make_shared<SmallestFirstSingle>()))));
    std::shared_ptr<Player> player2 = std::make_shared<HumanPlayer>(input_interface); 
    std::shared_ptr<Player> player3 = std::make_shared<HumanPlayer>(input_interface); 
    std::shared_ptr<Player> player4 = std::make_shared<HumanPlayer>(input_interface); 
    
    RunNewGame(input_interface, output_interface, {player1, player2, player3, player4});
}

void AllAiPlay() {
    std::string output_file_name = kDirectoryName + "my_output/" + "all_ai.test.out";
    std::shared_ptr<InputInterface> input_interface = std::make_shared<InputInterfaceTerminal>();
    std::shared_ptr<OutputInterface> output_interface = std::make_shared<OutputInterface>(output_file_name);

    std::shared_ptr<Player> straight_first_ai = 
            std::make_shared<AiPlayer>(std::make_shared<SmallestFirstStraight>(
                                       std::make_shared<SmallestFirstFullHouse>(
                                       std::make_shared<SmallestFirstPair>(
                                       std::make_shared<SmallestFirstSingle>()))),
                                       "straight_first");
    std::shared_ptr<Player> full_house_first_ai = 
            std::make_shared<AiPlayer>(std::make_shared<SmallestFirstFullHouse>(
                                       std::make_shared<SmallestFirstStraight>(
                                       std::make_shared<SmallestFirstPair>(
                                       std::make_shared<SmallestFirstSingle>()))),
                                       "full_house_first");
    std::shared_ptr<Player> pair_first_ai = 
            std::make_shared<AiPlayer>(std::make_shared<SmallestFirstPair>(
                                       std::make_shared<SmallestFirstSingle>(
                                       std::make_shared<SmallestFirstStraight>(
                                       std::make_shared<SmallestFirstFullHouse>()))),
                                       "pair_first");
    std::shared_ptr<Player> single_first_ai = 
            std::make_shared<AiPlayer>(std::make_shared<SmallestFirstSingle>(
                                       std::make_shared<SmallestFirstPair>(
                                       std::make_shared<SmallestFirstFullHouse>(
                                       std::make_shared<SmallestFirstStraight>()))),
                                       "single_first");
    
    RunNewGame(input_interface, output_interface, {straight_first_ai, full_house_first_ai, pair_first_ai, single_first_ai});
}

void RunNewGame(std::shared_ptr<InputInterface> input_interface, 
                std::shared_ptr<OutputInterface> output_interface,
                std::vector<std::shared_ptr<Player>> players) {
    std::shared_ptr<CardPatternParser> card_pattern_parser = std::make_shared<StraightParser>(
                                                             std::make_shared<FullHouseParser>(
                                                             std::make_shared<PairParser>(
                                                             std::make_shared<SingleParser>())));

    Big2 big2(input_interface, output_interface, card_pattern_parser);
    for (const auto& player : players)
        big2.AddPlayer(player);

    big2.Start();
}
