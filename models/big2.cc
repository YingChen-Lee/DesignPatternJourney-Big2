#include "big2.h"

Big2::Big2(InputInterface& input_interface, OutputInterface& output_interface) :
    input_interface_(input_interface),
    output_interface_(output_interface) {
}

void Big2::AddPlayer(std::shared_ptr<Player> player) {
    players_.push_back(player);
}

void Big2::Start() {


}