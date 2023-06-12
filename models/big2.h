#pragma once

#include <memory>
#include <vector>

#include "commandline_interface/input_interface.h"
#include "commandline_interface/output_interface.h"
#include "card_pattern/card_pattern.h"
#include "player.h"

class Big2 {
public:
    Big2(InputInterface& input_interface, OutputInterface& output_interface);
    void AddPlayer(std::shared_ptr<Player> player);
    void Start();

private:
    std::shared_ptr<Player> top_player_;
    std::shared_ptr<CardPattern> top_play_;
    
    std::vector<std::shared_ptr<Player>> players_;

    InputInterface& input_interface_;
    OutputInterface& output_interface_;
};