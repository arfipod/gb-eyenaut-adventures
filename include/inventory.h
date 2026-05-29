#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include <stdint.h>

#define INVENTORY_SLOT_COUNT 8u
#define INVENTORY_ITEM_COUNT 11u
#define RECIPE_COUNT 8u
#define INVENTORY_MAX_COUNT 99u
#define TOOL_LEVEL_HAND 0u
#define TOOL_LEVEL_STONE 1u
#define TOOL_LEVEL_IRON 2u
#define TOOL_LEVEL_NONE TOOL_LEVEL_HAND
#define TOOL_LEVEL_BASIC TOOL_LEVEL_STONE
#define CRAFT_STATUS_OK 0u
#define CRAFT_STATUS_NEEDS_WORKBENCH 1u
#define CRAFT_STATUS_NEEDS_MATERIAL 2u
#define CRAFT_STATUS_OUTPUT_BLOCKED 3u
#define CRAFT_STATUS_ALREADY_OWNED 4u

#define ITEM_DIRT 0u
#define ITEM_STONE 1u
#define ITEM_WOOD 2u
#define ITEM_PLANK 3u
#define ITEM_WORKBENCH 4u
#define ITEM_TORCH 5u
#define ITEM_PLATFORM 6u
#define ITEM_DOOR 7u
#define ITEM_COAL 8u
#define ITEM_COPPER 9u
#define ITEM_IRON 10u
#define ITEM_NONE 255u

typedef struct Recipe {
    uint8_t output_item;
    uint8_t output_count;
    uint8_t output_tool_level;
    uint8_t input_a;
    uint8_t input_a_count;
    uint8_t input_b;
    uint8_t input_b_count;
    uint8_t requires_workbench;
} Recipe;

typedef struct Inventory {
    uint8_t counts[INVENTORY_ITEM_COUNT];
    uint8_t tool_level;
    uint8_t selected_slot;
    uint8_t selected_recipe;
} Inventory;

void inventory_init(Inventory *inventory);
bool inventory_can_add_item(const Inventory *inventory, uint8_t item, uint8_t count);
void inventory_add_item(Inventory *inventory, uint8_t item, uint8_t count);
void inventory_add_block(Inventory *inventory, uint8_t tile);
bool inventory_consume_item(Inventory *inventory, uint8_t item, uint8_t count);
bool inventory_consume_selected(Inventory *inventory);
void inventory_next_slot(Inventory *inventory);
void inventory_prev_slot(Inventory *inventory);
uint8_t inventory_selected_tile(const Inventory *inventory);
uint8_t inventory_item_tile(uint8_t item);
uint8_t inventory_item_for_tile(uint8_t tile);
uint8_t inventory_tool_tile(uint8_t tool_level);
uint8_t inventory_tile_required_tool_level(uint8_t tile);
bool inventory_can_mine_tile(const Inventory *inventory, uint8_t tile);
const Recipe *inventory_recipe(uint8_t recipe_index);
void inventory_next_recipe(Inventory *inventory);
void inventory_prev_recipe(Inventory *inventory);
uint8_t inventory_craft_status(const Inventory *inventory, uint8_t recipe_index, bool near_workbench);
bool inventory_recipe_input_missing(const Inventory *inventory, uint8_t recipe_index, uint8_t input_index);
bool inventory_can_craft(const Inventory *inventory, uint8_t recipe_index, bool near_workbench);
bool inventory_craft_selected(Inventory *inventory, bool near_workbench);

#endif
