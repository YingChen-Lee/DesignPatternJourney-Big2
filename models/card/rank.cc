#include "rank.h"

#include <string>
#include <iostream>

const std::unordered_map<RankEnum, std::string> Rank::rank_string_map = {
     {RankEnum::k3, "3"}, {RankEnum::k4, "4"}, {RankEnum::k5, "5"},
    {RankEnum::k6, "6"}, {RankEnum::k7, "7"}, {RankEnum::k8, "8"}, {RankEnum::k9, "9"},
    {RankEnum::k10, "10"}, {RankEnum::kJ, "J"}, {RankEnum::kQ, "Q"}, {RankEnum::kK, "K"},
    {RankEnum::kA, "A"}, {RankEnum::k2, "2"}
};

Rank::Rank(RankEnum rank): rank_(rank) {};

std::string Rank::ToString() const{
    return Rank::rank_string_map.at(rank_);
}

RankEnum Rank::get() const{
    return rank_;
}

void Rank::set(RankEnum rank) {
    rank_ = rank; 
} 

Rank& Rank::operator++(){
    if (rank_ == RankEnum::kA) {
        throw std::out_of_range("for operator++ Rank");
    }
    set(RankEnum(static_cast<int>(rank_) + 1));
    return *this;
}

bool Rank::operator==(const Rank& rank_rhs) const{
    return (rank_ == rank_rhs.rank_);
}

int Rank::ShowdownRank(Rank rank_rhs) const{
    return static_cast<int>(rank_) - static_cast<int>(rank_rhs.get());
}