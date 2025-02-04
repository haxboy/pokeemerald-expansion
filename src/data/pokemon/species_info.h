#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD(picTable, _size, shadow, _tracks, ...)                                    \
.overworldData = {                                                                          \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                         \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                             \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                               \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                              \
    .paletteSlot = PALSLOT_NPC_1,                                                           \
    .shadowSize = shadow,                                                                   \
    .inanimate = FALSE,                                                                     \
    .compressed = COMP,                                                                     \
    .tracks = _tracks,                                                                      \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64), \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),         \
    .anims = sAnimTable_Following,                                                          \
    .images = picTable,                                                                     \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
},                                                                                          \
    OVERWORLD_PAL(__VA_ARGS__)

#define OVERWORLD_SET_ANIM(picTable, _size, shadow, _tracks, _anims, ...)                   \
.overworldData = {                                                                          \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                         \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                             \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                               \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                              \
    .paletteSlot = PALSLOT_NPC_1,                                                           \
    .shadowSize = shadow,                                                                   \
    .inanimate = FALSE,                                                                     \
    .compressed = COMP,                                                                     \
    .tracks = _tracks,                                                                      \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64), \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),         \
    .anims = _anims,                                                                        \
    .images = picTable,                                                                     \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
},                                                                                          \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(picTable, _size, shadow, _tracks, ...)                             \
.overworldDataFemale = {                                                                    \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                         \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                             \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                               \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                              \
    .paletteSlot = PALSLOT_NPC_1,                                                           \
    .shadowSize = shadow,                                                                   \
    .inanimate = FALSE,                                                                     \
    .compressed = COMP,                                                                     \
    .tracks = _tracks,                                                                      \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64), \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),         \
    .anims = sAnimTable_Following,                                                          \
    .images = picTable,                                                                     \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
},                                                                                          \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(picTable, _size, shadow, _tracks, ...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(picTable, _size, shadow, _tracks, ...)
#define OVERWORLD_SET_ANIM(picTable, _size, shadow, _tracks, _anims, ...)
#define OVERWORLD_FEMALE(picTable, _size, shadow, _tracks, ...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_None,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
            .affineAnims = gDummySpriteAffineAnimTable,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    [SPECIES_SKERRIBBLE] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER,TYPE_ROCK),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Skerribble"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_SKERRIBBLE,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_THISTLETOT] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Thistletot"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_THISTLETOT,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_BRISTLEBLOOM] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Bristlebloom"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_BRISTLEBLOOM,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_THORNAMENT] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Thornament"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_THORNAMENT,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_CALFIRE] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Calfire"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_CALFIRE,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_BLAZEBELL] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Blazebell"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_BLAZEBELL,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_PYROHIGH] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Pyrohigh"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_PYROHIGH,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_PUFFLET] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Pufflet"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_PUFFLET,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_TUFFIN] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Tuffin"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_TUFFIN,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_GULPUFF] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Gulpuff"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_GULPUFF,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_BOGLIN] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DARK,TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Boglin"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_BOGLIN,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_CREMELETTE] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Crèmelette"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_CREMELETTE,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_RASPBERRYNE] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Raspberryne"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_RASPBERRYNE,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_DRACELT] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DRAGON,TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Dracelt"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_DRACELT,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_AURORANE] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_FAIRY,TYPE_FLYING),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Aurorane"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_AURORANE,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_UMBRATHAL] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DARK,TYPE_GROUND),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Umbrathal"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_UMBRATHAL,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    [SPECIES_NYMPHALGA] =
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpeed     = 40,
        .baseSpAttack  = 55,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER,TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1,EGG_GROUP_MONSTER),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Nymphalga"),
        .cryId = CRY_SKERRIBBLE,
        .natDexNum = NATIONAL_DEX_NYMPHALGA,
        .categoryName = _("New Species"),
        .height = 4,
        .weight = 75,
        .description = COMPOUND_STRING(
            "Skerribble spends its days perched on \n" 
            "rocky outcrops near the sea, blending \n"
            "into its surroundings with its barnacle-like shell."), 
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skerribble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skerribble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMark,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        //.paletteFemale = gMonPalette_CircledQuestionMark,
        //.shinyPaletteFemale = gMonShinyPalette_CircledQuestionMark,
        //.iconSpriteFemale = gMonIcon_QuestionMark,
        //.iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skerribble,
        .shinyPalette = gMonShinyPalette_Skerribble,
        .iconSprite = gMonIcon_Skerribble,
        .iconPalIndex = 0,
        FOOTPRINT(Skerribble)
        .levelUpLearnset = sSkerribbleLevelUpLearnset,
        .teachableLearnset = sSkerribbleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
};
