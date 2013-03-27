#define WORDCOUNT 50
#define SUPERWORDCOUNT 3

int HangmanWordLists[SKILLCOUNT][WORDCOUNT] = 
{
    {
        "ant", "ball", "balloon", "cat", "play", "ant", "ball", "balloon",
        "cat", "play", "ant", "ball", "balloon", "cat", "play", "ant",
        "ball", "balloon", "cat", "play", "ant", "ball", "balloon", "cat",
        "play", "ant", "ball", "balloon", "cat", "play", "ant", "ball",
        "balloon", "cat", "play", "ant", "ball", "balloon", "cat", "play",
        "ant", "ball", "balloon", "cat", "play", "ant", "ball", "balloon",
        "cat", "play", 
    },

    {
        "america", "awesome", "cannon", "chocolate", "comical", "crazy", "diamond", "doom",
        "heavy", "insane", "king", "metal", "over", "porcupine", "powered", "quack",
        "skull", "tag", "tree", "america", "awesome", "cannon", "chocolate", "comical",
        "crazy", "diamond", "doom", "heavy", "insane", "king", "metal", "over",
        "porcupine", "powered", "quack", "skull", "tag", "tree", "america", "awesome",
        "cannon", "chocolate", "comical", "crazy", "diamond", "doom", "heavy", "insane",
        "king", "metal", 
    },

    {
        "aghast", "brazen", "brevity", "bullshit", "cancer", "cistern", "crimson", "egyptian",
        "excruciating", "exploit", "fascinating", "googol", "granularity", "lackluster", "lampoon", "multitask",
        "muse", "nailgun", "obscure", "obsidian", "polearm", "quake", "ranger", "rhythm",
        "simplicity", "smartass", "superconductivity", "surreal", "aghast", "brazen", "brevity", "bullshit",
        "cancer", "cistern", "crimson", "egyptian", "excruciating", "exploit", "fascinating", "googol",
        "granularity", "lackluster", "lampoon", "multitask", "muse", "nailgun", "obscure", "obsidian",
        "polearm", "quake", 
    },

    {
        "acerbic", "acrimony", "aphorism", "apocryphal", "archaic", "capricious", "chicanery", "demagogue",
        "disengenious", "efficacy", "eloquence", "equivocate", "etymology", "euclidian", "forbearance", "halcyon",
        "hierarchy", "histogram", "hyperbola", "iconoclast", "inscrutable", "layby", "lexicon", "logomachy",
        "loquacious", "lynx", "metaclassing", "metamorphic", "milieu", "modularity", "myopic", "nootropic",
        "obviate", "pauldron", "pecuniary", "phylactery", "proclivity", "puerile", "pusillanimous", "renege",
        "reticent", "scintilla", "sojourn", "spectrograph", "syllogism", "tautological", "terminus", "ubiquitous",
        "vilify", "vitiate", 
    },

    {
        "ablutomania", "absquatulate", "anautarchia", "baffona", "bradykinin", "dactylion", "deuterium", "eccedentesiast",
        "erinaceous", "fabiform", "fourier", "gabelle", "hyoid", "jentacular", "jobbernowl", "kazatzka",
        "knismesis", "lexiphanic", "necrotype", "orgulous", "pauciloquent", "philosophaster", "pyknic", "pyx",
        "qua", "quipu", "quodlibet", "scacchic", "thob", "tittynope", "tyromancy", "varsovienne",
        "winklepicker", "wyn", "xanthic", "xylophilous", "yarborough", "yclept", "yestreen", "zenzizenzizenzic",
        "zoanthropy", "zoppetto", "ablutomania", "absquatulate", "anautarchia", "baffona", "bradykinin", "dactylion",
        "deuterium", "eccedentesiast", 
    },
};

int HangmanSuperWords[SUPERWORDCOUNT] = 
{
    "bird", "internet", "lol", 
};
