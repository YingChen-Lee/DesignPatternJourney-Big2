#pragma once

#include <string>
#include <vector>

#include "input_interface.h"

#include "../models/deck.h"

class InputInterfaceTerminal : public InputInterface {
public:
    InputInterfaceTerminal() = default;
    virtual ~InputInterfaceTerminal() = default;

    virtual std::string GetNextPlayerName() override ;
    virtual std::vector<int> GetNextPlayIndices() override ;
};
