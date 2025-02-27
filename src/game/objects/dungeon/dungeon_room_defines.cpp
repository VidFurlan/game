#include "dungeon.hpp"

// clang-format off
const std::unordered_map<DungeonRoom::Type, std::vector<std::vector<Dungeon::EntityData>>>
Dungeon::mRoomConfigs ({
	    {DungeonRoom::Type::MONSTER, {
                {
                    {EntityType::GRAY_BLOB, {-20.0f, 20.0f}},
                    {EntityType::GRAY_BLOB, {-20.0f, -20.0f}},
                    {EntityType::GRAY_BLOB, {20.0f, -20.0f}},
                    {EntityType::GRAY_BLOB, {20.0f, 20.0f}}
                },
                {{EntityType::GRAY_BLOB, {0.0f, 0.0f}}}
        }},
        {DungeonRoom::Type::TREASURE, {
                {{EntityType::TREASURE_CHEST, {0.0f, 0.0f}}},
        }},
    });
// clang-format on
