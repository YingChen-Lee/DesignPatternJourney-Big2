#pragma once

#include <string>
#include <vector>

#include "../models/deck.h"

class InputInterface {
public:
    InputInterface() = default;
    virtual ~InputInterface() = default;

    virtual Deck GetDeck(); 
    virtual std::string GetNextPlayerName() = 0;
    virtual std::vector<int> GetNextPlayIndices() = 0;
};
