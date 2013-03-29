#define WORDCOUNT 103
#define SUPERWORDCOUNT 3

int HangmanWordLists[SKILLCOUNT][WORDCOUNT] = 
{
    {
        "above", "accounts", "afford", "alive", "alive", "ant", "awesome", "ball",
        "balloon", "below", "bishop", "bordering", "bullshit", "burn", "buzzes", "cannon",
        "clung", "desirable", "dine", "dish", "doom", "driving", "everything", "fixes",
        "gray", "heavy", "hooked", "hummed", "incompetence", "intellect", "invest", "king",
        "leave", "lightly", "listened", "logic", "metal", "nearby", "none", "over",
        "perverted", "play", "potato", "power", "provides", "quack", "rotating", "shaped",
        "simple", "skull", "smartass", "southwest", "stickers", "subtraction", "swan", "tag",
        "taker", "tasked", "tomato", "train", "vocabulary", "wake", "words", "above",
        "accounts", "afford", "alive", "alive", "ant", "awesome", "ball", "balloon",
        "below", "bishop", "bordering", "bullshit", "burn", "buzzes", "cannon", "clung",
        "desirable", "dine", "dish", "doom", "driving", "everything", "fixes", "gray",
        "heavy", "hooked", "hummed", "incompetence", "intellect", "invest", "king", "leave",
        "lightly", "listened", "logic", "metal", "nearby", "none", "over", 
    },

    {
        "advantages", "aerial", "alternative", "america", "antonym", "aquatic", "average", "baseballs",
        "battlegrounds", "bombardment", "boon", "boundless", "canals", "cancer", "cartridges", "chocolate",
        "cistern", "civilized", "comical", "construction", "crazy", "decays", "decomposing", "degenerated",
        "demonstrated", "destruction", "dew", "diamond", "diversity", "draining", "dropper", "egyptian",
        "errors", "evidently", "exceed", "existed", "exploit", "extensively", "fascinating", "frontal",
        "gaping", "garner", "geyser", "hotshot", "imprisoning", "inattention", "infamous", "infinite",
        "insane", "insurance", "invisible", "keeper", "kicker", "lackluster", "leggings", "matches",
        "mechanical", "meekly", "mellowing", "metaphorically", "metro", "monumental", "motherly", "naughtiness",
        "notch", "obscene", "obscure", "onrush", "pamper", "paperwork", "perishing", "photographed",
        "porcupine", "porpoise", "possible", "previewed", "propels", "redistribute", "reflexive", "representation",
        "resulted", "rhyming", "rhythm", "ruse", "salvage", "selection", "slicks", "snugly",
        "stepmother", "storminess", "suffocate", "synonym", "tasteless", "thoughtlessness", "totalling", "tree",
        "trustworthy", "unaffected", "unbelievable", "unholy", "uniquely", "voluntarily", "weasels", 
    },

    {
        "Poseidon", "abrasions", "adages", "aggregate", "aghast", "aids", "alienates", "allays",
        "annihilation", "aqueous", "archaic", "barkeep", "befallen", "bifocals", "bolster", "bombastic",
        "brazen", "brevity", "ceasing", "coinciding", "conceivable", "conductive", "consolers", "covetous",
        "crimson", "dehumanization", "delineate", "delirium", "dicky", "discrepant", "distilling", "dogtooth",
        "excruciating", "facet", "fatigues", "gargoyle", "googol", "granularity", "illogically", "incentive",
        "ineffable", "inscrutable", "intimacy", "itemizing", "lacerates", "lackluster", "lampoon", "limelight",
        "luscious", "magnifier", "maternity", "multitask", "muse", "nailgun", "node", "objective",
        "obscurities", "obsidian", "osmosis", "panacea", "paternity", "pedantic", "periphery", "polearm",
        "prevalence", "pulverization", "quake", "queued", "ranger", "renaissance", "sacking", "sanctimonious",
        "scimitar", "simplicity", "skirmish", "sputter", "subjective", "sullenness", "supplicate", "surreal",
        "tapestries", "tempter", "tribunals", "trite", "typeface", "Poseidon", "abrasions", "adages",
        "aggregate", "aghast", "aids", "alienates", "allays", "annihilation", "aqueous", "archaic",
        "barkeep", "befallen", "bifocals", "bolster", "bombastic", "brazen", "brevity", 
    },

    {
        "acerbic", "acrimony", "aeronautics", "aphorism", "apocryphal", "auk", "besmirches", "capricious",
        "chicanery", "demagogue", "deuterium", "disengenious", "eddies", "efficacy", "eloquence", "equivocate",
        "etymology", "euclidian", "euthanasia", "forbearance", "fourier", "germination", "halcyon", "hierarchy",
        "histogram", "hyperbola", "iconoclast", "layby", "lexicon", "logomachy", "loquacious", "luge",
        "lynx", "metaclassing", "metamorphic", "milieu", "modularity", "myopic", "neurological", "nootropic",
        "obviate", "outlays", "pasteup", "pauldron", "pecuniary", "peepy", "phylactery", "phytoplankton",
        "proclivity", "puerile", "pusillanimous", "quintic", "renege", "reticent", "schizoid", "scintilla",
        "sojourn", "spectrograph", "spikenard", "stroboscopic", "syllogism", "syndic", "tappet", "tautological",
        "terminus", "ubiquitous", "vilify", "virtuosity", "vitiate", "winningly", "acerbic", "acrimony",
        "aeronautics", "aphorism", "apocryphal", "auk", "besmirches", "capricious", "chicanery", "demagogue",
        "deuterium", "disengenious", "eddies", "efficacy", "eloquence", "equivocate", "etymology", "euclidian",
        "euthanasia", "forbearance", "fourier", "germination", "halcyon", "hierarchy", "histogram", "hyperbola",
        "iconoclast", "layby", "lexicon", "logomachy", "loquacious", "luge", "lynx", 
    },

    {
        "ablutomania", "absquatulate", "anautarchia", "baffona", "bradykinin", "dactylion", "delicti", "eccedentesiast",
        "erinaceous", "fabiform", "gabelle", "hyoid", "jentacular", "jobbernowl", "kazatzka", "knismesis",
        "lexiphanic", "lipschitz", "matriculate", "necrotype", "orgulous", "pauciloquent", "philosophaster", "pyknic",
        "pyx", "qua", "quipu", "quodlibet", "scacchic", "thob", "tittynope", "tyromancy",
        "varsovienne", "winklepicker", "wyn", "xanthic", "xylophilous", "yarborough", "yclept", "yestreen",
        "zenzizenzizenzic", "zoanthropy", "zoppetto", "ablutomania", "absquatulate", "anautarchia", "baffona", "bradykinin",
        "dactylion", "delicti", "eccedentesiast", "erinaceous", "fabiform", "gabelle", "hyoid", "jentacular",
        "jobbernowl", "kazatzka", "knismesis", "lexiphanic", "lipschitz", "matriculate", "necrotype", "orgulous",
        "pauciloquent", "philosophaster", "pyknic", "pyx", "qua", "quipu", "quodlibet", "scacchic",
        "thob", "tittynope", "tyromancy", "varsovienne", "winklepicker", "wyn", "xanthic", "xylophilous",
        "yarborough", "yclept", "yestreen", "zenzizenzizenzic", "zoanthropy", "zoppetto", "ablutomania", "absquatulate",
        "anautarchia", "baffona", "bradykinin", "dactylion", "delicti", "eccedentesiast", "erinaceous", "fabiform",
        "gabelle", "hyoid", "jentacular", "jobbernowl", "kazatzka", "knismesis", "lexiphanic", 
    },
};

int HangmanSuperWords[SUPERWORDCOUNT] = 
{
    "bird", "internet", "lol", 
};
