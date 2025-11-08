#pragma once
#include <bitset>
#include <cstdint>

using Entity                              = std::uint32_t;
static const Entity MAX_ENTITIES          = 8192;
using ComponentType                       = std::uint8_t;
static const ComponentType MAX_COMPONENTS = 64;
using Signature                           = std::bitset<MAX_COMPONENTS>;
