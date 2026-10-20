#pragma once

#include "elf.hpp"
#include "r5900.hpp"

#include <cstdint>
#include <set>
#include <vector>

namespace recomp {

struct Program {
    std::uint32_t base{};
    std::uint32_t end{};
    std::vector<std::uint8_t> code;
    std::set<std::uint32_t> functions;
    std::set<std::uint32_t> entries;
    std::set<std::uint32_t> rejected;
    std::set<std::uint32_t> dynamic;

    bool is_code(std::uint32_t address) const {
        return address >= base && address < end && (address & 3u) == 0 && code[(address - base) >> 2];
    }
};

Program analyse(const Image &image, const std::vector<std::uint32_t> &extra_entries, const std::set<std::uint32_t> &dynamic = {});

// Likely function starts that the analyser cannot reach by following flow: an `addiu sp, sp, -N`
// followed by a store to sp, the way tools/prologues.py seeds them.
std::vector<std::uint32_t> prologue_starts(const Image &image);

}
