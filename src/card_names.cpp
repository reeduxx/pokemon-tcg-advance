#include "card_names.h"

static const char* const card_names[] = {
	// Pokemon
	"BULBASAUR",
	"ERIKA'S BULBASAUR",
	"IVYSAUR",
	"ERIKA'S IVYSAUR",
	"VENUSAUR",
	"ERIKA'S VENUSAUR",
	"CHARMANDER",
	"BLAINE'S CHARMANDER",
	"CHARMELEON",
	"BLAINE'S CHARMELEON",
	"DARK CHARMELEON",
	"CHARIZARD",
	"BLAINE'S CHARIZARD",
	"DARK CHARIZARD",
	"SHINING CHARIZARD",
	"SQUIRTLE",
	"WARTORTLE",
	"DARK WARTORTLE",
	"BLASTOISE",
	"DARK BLASTOISE",
	"CATERPIE",
	"METAPOD",
	"BUTTERFREE",
	"WEEDLE",
	"KOGA'S WEEDLE",
	"KAKUNA",
	"KOGA'S KAKUNA",
	"BEEDRILL",
	"KOGA'S BEEDRILL",
	"PIDGEY",
	"KOGA'S PIDGEY",
	"PIDGEOTTO",
	"KOGA'S PIDGEOTTO",
	"PIDGEOT",
	"RATTATA",
	"LT. SURGE'S RATTATA",
	"RATICATE",
	"DARK RATICATE",
	"LT. SURGE'S RATICATE",
	"SPEAROW",
	"LT. SURGE'S SPEAROW",
	"FEAROW",
	"LT. SURGE'S FEAROW",
	"EKANS",
	"KOGA'S EKANS",
	"ARBOK",
	"DARK ARBOK",
	"KOGA'S ARBOK",
	"PIKACHU",
	"LT. SURGE'S PIKACHU",
	"RAICHU",
	"DARK RAICHU",
	"LT. SURGE'S RAICHU",
	"SHINING RAICHU",
	"SANDSHREW",
	"BROCK'S SANDSHREW",
	"SANDSLASH",
	"BROCK'S SANDSLASH",
	"NIDORAN♀",
	"GIOVANNI'S NIDORAN♀",
	"NIDORINA",
	"GIOVANNI'S NIDORINA",
	"NIDOQUEEN",
	"GIOVANNI'S NIDOQUEEN",
	"NIDORAN♂",
	"GIOVANNI'S NIDORAN♂",
	"NIDORINO",
	"GIOVANNI'S NIDORINO",
	"NIDOKING",
	"GIOVANNI'S NIDOKING",
	"CLEFAIRY",
	"ERIKA'S CLEFAIRY",
	"CLEFABLE",
	"ERIKA'S CLEFABLE",
	"VULPIX",
	"BLAINE'S VULPIX",
	"BROCK'S VULPIX",
	"NINETALES",
	"BLAINE'S NINETALES",
	"BROCK'S NINETALES",
	"LIGHT NINETALES",
	"JIGGLYPUFF",
	"ERIKA'S JIGGLYPUFF",
	"WIGGLYTUFF",
	"DARK WIGGLYTUFF",
	"LIGHT WIGGLYTUFF",
	"ZUBAT",
	"BROCK'S ZUBAT",
	"KOGA'S ZUBAT",
	"GOLBAT",
	"BROCK'S GOLBAT",
	"DARK GOLBAT",
	"KOGA'S GOLBAT",
	"ODDISH",
	"ERIKA'S ODDISH",
	"GLOOM",
	"DARK GLOOM",
	"ERIKA'S GLOOM",
	"VILEPLUME",
	"DARK VILEPLUME",
	"ERIKA'S VILEPLUME",
	"PARAS",
	"ERIKA'S PARAS",
	"PARASECT",
	"VENONAT",
	"SABRINA'S VENONAT",
	"VENOMOTH",
	"LIGHT VENOMOTH",
	"SABRINA'S VENOMOTH",
	"DIGLETT",
	"BROCK'S DIGLETT",
	"DUGTRIO",
	"BROCK'S DUGTRIO",
	"MEOWTH",
	"GIOVANNI'S MEOWTH",
	"PERSIAN",
	"DARK PERSIAN",
	"GIOVANNI'S PERSIAN",
	"PSYDUCK",
	"MISTY'S PSYDUCK",
	"SABRINA'S PSYDUCK",
	"GOLDUCK",
	"DARK GOLDUCK",
	"LIGHT GOLDUCK",
	"MISTY'S GOLDUCK",
	"SABRINA'S GOLDUCK",
	"MANKEY",
	"BLAINE'S MANKEY",
	"BROCK'S MANKEY",
	"PRIMEAPE",
	"BROCK'S PRIMEAPE",
	"DARK PRIMEAPE",
	"GROWLITHE",
	"BLAINE'S GROWLITHE",
	"ARCANINE",
	"BLAINE'S ARCANINE",
	"LIGHT ARCANINE",
	"POLIWAG",
	"MISTY'S POLIWAG",
	"POLIWHIRL",
	"MISTY'S POLIWHIRL",
	"POLIWRATH",
	"MISTY'S POLIWRATH",
	"ABRA",
	"SABRINA'S ABRA",
	"KADABRA",
	"DARK KADABRA",
	"SABRINA'S KADABRA",
	"ALAKAZAM",
	"DARK ALAKAZAM",
	"SABRINA'S ALAKAZAM",
	"MACHOP",
	"GIOVANNI'S MACHOP",
	"MACHOKE",
	"DARK MACHOKE",
	"GIOVANNI'S MACHOKE",
	"LIGHT MACHOKE",
	"MACHAMP",
	"DARK MACHAMP",
	"GIOVANNI'S MACHAMP",
	"LIGHT MACHAMP",
	"BELLSPROUT",
	"ERIKA'S BELLSPROUT",
	"WEEPINBELL",
	"ERIKA'S WEEPINBELL",
	"VICTREEBEL",
	"ERIKA'S VICTREEBEL",
	"TENTACOOL",
	"MISTY'S TENTACOOL",
	"TENTACRUEL",
	"MISTY'S TENTACRUEL",
	"KOFFING",
	"KOGA'S KOFFING",
	"WEEZING",
	"DARK WEEZING",
	"KOGA'S WEEZING",
	"GEODUDE",
	"BROCK'S GEODUDE",
	"GRAVELER",
	"BROCK'S GRAVELER",
	"GOLEM",
	"BROCK'S GOLEM",
	"PONYTA",
	"BLAINE'S PONYTA",
	"RAPIDASH",
	"BLAINE'S RAPIDASH",
	"DARK RAPIDASH",
	"SLOWPOKE",
	"SABRINA'S SLOWPOKE",
	"SLOWBRO",
	"DARK SLOWBRO",
	"LIGHT SLOWBRO",
	"SABRINA'S SLOWBRO",
	"MAGNEMITE",
	"LT. SURGE'S MAGNEMITE",
	"MAGNETON",
	"DARK MAGNETON",
	"LT. SURGE'S MAGNETON",
	"FARFETCH'D",
	"DODUO",
	"BLAINE'S DODUO",
	"IMAKUNI?'S DODUO",
	"DODRIO",
	"SEEL",
	"MISTY'S SEEL",
	"DEWGONG",
	"LIGHT DEWGONG",
	"MISTY'S DEWGONG",
	"GRIMER",
	"KOGA'S GRIMER",
	"MUK",
	"DARK MUK",
	"KOGA'S MUK",
	"SHELLDER",
	"MISTY'S SHELLDER",
	"CLOYSTER",
	"MISTY'S CLOYSTER",
	"GASTLY",
	"SABRINA'S GASTLY",
	"HAUNTER",
	"DARK HAUNTER",
	"SABRINA'S HAUNTER",
	"GENGAR",
	"DARK GENGAR",
	"SABRINA'S GENGAR",
	"ONIX",
	"BROCK'S ONIX",
	"DROWZEE",
	"SABRINA'S DROWZEE",
	"HYPNO",
	"DARK HYPNO",
	"SABRINA'S HYPNO",
	"KRABBY",
	"KINGLER",
	"VOLTORB",
	"LT. SURGE'S VOLTORB",
	"ELECTRODE",
	"DARK ELECTRODE",
	"EXEGGCUTE",
	"ERIKA'S EXEGGCUTE",
	"EXEGGUTOR",
	"DARK EXEGGUTOR",
	"ERIKA'S EXEGGUTOR",	
	"CUBONE",
	"MAROWAK",
	"HITMONLEE",
	"HITMONCHAN",
	"BROCK'S HITMONCHAN",
	"LICKITUNG",
	"BROCK'S LICKITUNG",
	"RHYHORN",
	"BLAINE'S RHYHORN",
	"BROCK'S RHYHORN",
	"RHYDON",
	"BROCK'S RHYDON",
	"CHANSEY",
	"_____'S CHANSEY",
	"TANGELA",
	"ERIKA'S TANGELA",
	"KOGA'S TANGELA",
	"KANGASKHAN",
	"BLAINE'S KANGASKHAN",
	"HORSEA",
	"MISTY'S HORSEA",
	"SEADRA",
	"MISTY'S SEADRA",
	"GOLDEEN",
	"MISTY'S GOLDEEN",
	"SEAKING",
	"MISTY'S SEAKING",
	"STARYU",
	"MISTY'S STARYU",
	"STARMIE",
	"MISTY'S STARMIE",
	"MR. MIME",
	"SABRINA'S MR. MIME",
	"SCYTHER",
	"ROCKET'S SCYTHER",
	"JYNX",
	"SABRINA'S JYNX",
	"ELECTABUZZ",
	"LT. SURGE'S ELECTABUZZ",
	"MAGMAR",
	"BLAINE'S MAGMAR",
	"PINSIR",
	"GIOVANNI'S PINSIR",
	"TAUROS",
	"BLAINE'S TAUROS",
	"MAGIKARP",
	"GIOVANNI'S MAGIKARP",
	"MISTY'S MAGIKARP",
	"SHINING MAGIKARP",
	"GYARADOS",
	"DARK GYARADOS",
	"GIOVANNI'S GYARADOS",
	"MISTY'S GYARADOS",
	"SHINING GYARADOS",
	"LAPRAS",
	"DITTO",
	"KOGA'S DITTO",
	"EEVEE",
	"LT. SURGE'S EEVEE",
	"VAPOREON",
	"DARK VAPOREON",
	"LIGHT VAPOREON",
	"JOLTEON",
	"DARK JOLTEON",
	"LIGHT JOLTEON",
	"LT. SURGE'S JOLTEON",
	"FLAREON",
	"DARK FLAREON",
	"LIGHT FLAREON",
	"PORYGON",
	"SABRINA'S PORYGON",
	"OMANYTE",
	"DARK OMANYTE",
	"OMASTAR",
	"DARK OMASTAR",
	"KABUTO",
	"KABUTOPS",
	"SHINING KABUTOPS",
	"AERODACTYL",
	"SNORLAX",
	"ROCKET'S SNORLAX",
	"ARTICUNO",
	"ZAPDOS",
	"ROCKET'S ZAPDOS",
	"MOLTRES",
	"BLAINE'S MOLTRES",
	"ROCKET'S MOLTRES",
	"DRATINI",
	"ERIKA'S DRATINI",
	"DRAGONAIR",
	"DARK DRAGONAIR",
	"ERIKA'S DRAGONAIR",
	"LIGHT DRAGONAIR",
	"DRAGONITE",
	"DARK DRAGONITE",
	"LIGHT DRAGONITE",
	"MEWTWO",
	"ROCKET'S MEWTWO",
	"SHINING MEWTWO",
	"MEW",
	"CHIKORITA",
	"BAYLEEF",
	"MEGANIUM",
	"CYNDAQUIL",
	"QUILAVA",
	"DARK QUILAVA",
	"TYPHLOSION",
	"DARK TYPHLOSION",
	"TOTODILE",
	"CROCONAW",
	"DARK CROCONAW",
	"FERALIGATR",
	"DARK FERALIGATR",
	"SENTRET",
	"FURRET",
	"HOOTHOOT",
	"NOCTOWL",
	"SHINING NOCTOWL",
	"LEDYBA",
	"LEDIAN",
	"LIGHT LEDIAN",
	"SPINARAK",
	"ARIADOS",
	"DARK ARIADOS",
	"CROBAT",
	"DARK CROBAT",
	"CHINCHOU",
	"LANTURN",
	"LIGHT LANTURN",
	"PICHU",
	"CLEFFA",
	"IGGLYBUFF",
	"TOGEPI",
	"TOGETIC",
	"LIGHT TOGETIC",
	"NATU",
	"XATU",
	"MAREEP",
	"FLAAFFY",
	"DARK FLAAFFY",
	"AMPHAROS",
	"DARK AMPHAROS",
	"BELLOSSOM",
	"MARILL",
	"AZUMARILL",
	"LIGHT AZUMARILL",
	"SUDOWOODO",
	"POLITOED",
	"HOPPIP",
	"SKIPLOOM",
	"JUMPLUFF",
	"AIPOM",
	"SUNKERN",
	"LIGHT SUNKERN",
	"SUNFLORA",
	"YANMA",
	"WOOPER",
	"QUAGSIRE",
	"ESPEON",
	"DARK ESPEON",
	"UMBREON",
	"MURKROW",
	"SLOWKING",
	"DARK SLOWKING",
	"MISDREAVUS",
	"UNOWN A",
	"UNOWN B",
	"UNOWN C",
	"UNOWN D",
	"UNOWN E",
	"UNOWN F",
	"UNOWN G",
	"UNOWN H",
	"UNOWN I",
	"UNOWN K",
	"UNOWN L",
	"UNOWN M",
	"UNOWN N",
	"UNOWN O",
	"UNOWN P",
	"UNOWN Q",
	"UNOWN S",
	"UNOWN T",
	"UNOWN U",
	"UNOWN V",
	"UNOWN W",
	"UNOWN X",
	"UNOWN Y",
	"UNOWN Z",
	"WOBBUFFET",
	"GIRAFARIG",
	"PINECO",
	"FORRETRESS",
	"DARK FORRETRESS",
	"DUNSPARCE",
	"GLIGAR",
	"STEELIX",
	"SHINING STEELIX",
	"SNUBBULL",
	"GRANBULL",
	"QWILFISH",
	"SCIZOR",
	"DARK SCIZOR",
	"SHUCKLE",
	"HERACROSS",
	"SNEASEL",
	"TEDDIURSA",
	"URSARING",
	"DARK URSARING",
	"SLUGMA",
	"MAGCARGO",
	"DARK MAGCARGO",
	"SWINUB",
	"PILOSWINE",
	"LIGHT PILOSWINE",
	"CORSOLA",
	"REMORAID",
	"OCTILLERY",
	"DARK OCTILLERY",
	"DELIBIRD",
	"MANTINE",
	"SKARMORY",
	"HOUNDOUR",
	"HOUNDOOM",
	"DARK HOUNDOOM",
	"KINGDRA",
	"PHANPY",
	"DONPHAN",
	"DARK DONPHAN",
	"PORYGON2",
	"DARK PORYGON2",
	"STANTLER",
	"SMEARGLE",
	"TYROGUE",
	"HITMONTOP",
	"SMOOCHUM",
	"ELEKID",
	"MAGBY",
	"MILTANK",
	"BLISSEY",
	"RAIKOU",
	"ENTEI",
	"SUICUNE",
	"LARVITAR",
	"PUPITAR",
	"DARK PUPITAR",
	"TYRANITAR",
	"DARK TYRANITAR",
	"SHINING TYRANITAR",
	"LUGIA",
	"HO-OH",
	"CELEBI",
	"SHINING CELEBI",
	// Trainers
	"ARCADE GAME",
	"BALLOON BERRY",
	"BERRY",
	"BILL",
	"BILL'S TELEPORTER",
	"BLAINE",
	"BLAINE'S GAMBLE",
	"BLAINE'S LAST RESORT",
	"BLAINE'S QUIZ #1",
	"BLAINE'S QUIZ #3",
	"BROCK",
	"BROCK'S PROTECTION",
	"BROCK'S TRAINING METHOD",
	"BROKEN GROUND GYM",
	"CARD-FLIP GAME",
	"CELADON CITY GYM",
	"CERULEAN CITY GYM",
	"CHALLENGE!",
	"CHAOS GYM",
	"CHARITY",
	"CINNABAR CITY GYM",
	"CLEFAIRY DOLL",
	"COMPUTER SEARCH",
	"COUNTERATTACK CLAWS",
	"DEFENDER",
	"DEVOLUTION SPRAY",
	"DIGGER",
	"DOUBLE GUST",
	"ECOGYM",
	"ENERGY AMPLIFIER",
	"ENERGY ARK",
	"ENERGY CHARGE",
	"ENERGY FLOW",
	"ENERGY REMOVAL",
	"ENERGY RETRIEVAL",
	"ENERGY SEARCH",
	"ENERGY STADIUM",
	"ERIKA",
	"ERIKA'S KINDNESS",
	"ERIKA'S MAIDS",
	"ERIKA'S PERFUME",
	"EXP ALL",
	"FERVOR",
	"FOCUS BAND",
	"FOSSIL EGG",
	"FUCHSIA CITY GYM",
	"FULL HEAL",
	"GAMBLER",
	"GIOVANNI",
	"GIOVANNI'S LAST RESORT",
	"GOLD BERRY",
	"GOOD MANNERS",
	"GOOP GAS ATTACK",
	"GUST OF WIND",
	"HEALING FIELD",
	"HEAL POWDER",
	"HERE COMES TEAM ROCKET!",
	"HYPER DEVOLUTION SPRAY",
	"IMPOSTER OAK'S INVENTION",
	"IMPOSTER OAK'S REVENGE",
	"IMPOSTER PROFESSOR OAK",
	"ITEM FINDER",
	"KOGA",
	"KOGA'S NINJA TRICK",
	"LASS",
	"LT. SURGE",
	"LT. SURGE'S SECRET PLAN",
	"LT. SURGE'S TREATY",
	"LUCKY STADIUM",
	"MAGNIFIER",
	"MAIL FROM BILL",
	"MAINTENANCE",
	"MARY",
	"MASTER BALL",
	"MAX REVIVE",
	"MINION OF TEAM ROCKET",
	"MIRACLE BERRY",
	"MISTY",
	"MISTY'S DUEL",
	"MISTY'S TEARS",
	"MISTY'S WISH",
	"MISTY'S WRATH",
	"MOO-MOO MILK",
	"MR. FUJI",
	"MYSTERIOUS FOSSIL",
	"NARROW GYM",
	"NEW POKéDEX",
	"NIGHTLY GARBAGE RUN",
	"NO REMOVAL GYM",
	"OLD ROD",
	"PEWTER CITY GYM",
	"PLUSPOWER",
	"POKé BALL",
	"POKéDEX",
	"POKéGEAR",
	"POKéMON BREEDER",
	"POKéMON BREEDER FIELDS",
	"POKéMON CENTER",
	"POKéMON FLUTE",
	"POKéMON MARCH",
	"POKéMON PERSONALITY TEST",
	"POKéMON TRADER",
	"POTION",
	"PROFESSOR ELM",
	"PROFESSOR OAK",
	"RADIO TOWER",
	"RECALL",
	"RECYCLE",
	"RESISTANCE GYM",
	"REVIVE",
	"ROCKET'S HIDEOUT",
	"ROCKET'S MINEFIELD GYM",
	"ROCKET'S SECRET EXPERIMENT",
	"ROCKET'S SNEAK ATTACK",
	"RUIN WALL",
	"SABRINA",
	"SABRINA'S ESP",
	"SABRINA'S GAZE",
	"SABRINA'S PSYCHIC CONTROL",
	"SAFFRON CITY GYM",
	"SCOOP UP",
	"SECRET MISSION",
	"SLEEP!",
	"SPROUT TOWER",
	"SUPER ENERGY REMOVAL",
	"SUPER ENERGY RETRIEVAL",
	"SUPER POTION",
	"SUPER ROD",
	"SUPER SCOOP UP",
	"SWITCH",
	"TEAM ROCKET'S EVIL DEEDS",
	"THE BOSS'S WAY",
	"THE ROCKET'S TRAINING GYM",
	"THE ROCKET'S TRAP",
	"THOUGHT WAVE MACHINE",
	"TICKLING MACHINE",
	"TIME CAPSULE",
	"TRANSPARENT WALLS",
	"TRASH EXCHANGE",
	"VERMILLION CITY GYM",
	"VIRIDIAN CITY GYM",
	"WARP POINT",
	// Energy
	"DARKNESS ENERGY",
	"DOUBLE COLORLESS ENERGY",
	"FIGHTING ENERGY",
	"FIRE ENERGY",
	"FULL HEAL ENERGY",
	"GRASS ENERGY",
	"LIGHTNING ENERGY",
	"METAL ENERGY",
	"MIRACLE ENERGY",
	"POTION ENERGY",
	"PSYCHIC ENERGY",
	"RAINBOW ENERGY",
	"RECYCLE ENERGY",
	"WATER ENERGY",
	"NONE"
};

const uint8_t CARD_NAME_COUNT = sizeof(card_names) / sizeof(card_names[0]);

const char* get_card_name(uint8_t name_id) {
	if(name_id >= CARD_NAME_COUNT) {
		return "NONE";
	}
	
	return card_names[name_id];
}
