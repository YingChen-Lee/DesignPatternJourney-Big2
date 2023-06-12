#pragma once

#include <string>
#include <unordered_map>

enum class RankEnum {
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    k10,
    kJ,
    kQ,
    kK,
    kA,
    k2
};

class Rank {
public:
    static const std::unordered_map<RankEnum, std::string> rank_string_map; 

    Rank(RankEnum rank);
    std::string ToString() const;
    RankEnum get() const;
    void set(RankEnum rank);
    Rank& operator++();
    int ShowdownRank(Rank rank_rhs) const;
private:
    RankEnum rank_;
};