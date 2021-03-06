#define HANGMAN_PICK            135
#define HANGMAN_PICKMENU        136

#define HANGMAN_ENTER           465
#define HANGMAN_RESPAWN         466
#define HANGMAN_SPAWN           467
#define HANGMAN_DEATH           468
#define HANGMAN_DISCONNECT      469

#define HANGMAN_WORDOPEN        481
#define HANGMAN_CHOOSEWORD      482
#define HANGMAN_ENDMENU         487

#define HANGMAN_PICK_SUCCESS    491
#define HANGMAN_PICK_FAIL       492
#define HANGMAN_WIN             493
#define HANGMAN_LOSE            494

#define HANGMAN_HUD             584
#define HANGMAN_PICKMENU_CLIENT 585

#define HANGMAN_REVEALLETTER    523
#define HANGMAN_SETGUESSES      524
#define HANGMAN_SETPICKED       525
#define HANGMAN_SETGAMESTATE    526

#define SETCOLORS               900

#define SKILLCOUNT  5

#define UNIQUEWORDCOUNT 4

#define HUD_CENTERX 80.0
#define HUD_CORNERY 104.0

global int 32:HangmanWords[];
global int 33:HangmanPickedChars[];
global int 34:HangmanGuessesLeft[];
global int 35:KnownLetters[];
global int 36:WordLengths[];

int InPickMenu[PLAYERMAX] = {0};
int PlayerTIDS[PLAYERMAX] = {0};
int HangmanOn           =  0;
int HangmanNoGuesses    =  0;
int WinningTeam         = -1;
int IsServer            = -1;

script SETCOLORS (int r, int g, int b) clientside
{
    int i, s;
    for(s = 0; s < 32767; s++)
    {
        Sector_SetColor(s, r, g, b);

        if (s % 10000 == 9999) { Delay(1); }
    }
}

int SkillNames[SKILLCOUNT] = { "Illiteracy", "Basic", "Normal", "Educated", "Dictionary" };

int TeamNames[TEAMCOUNT] = 
{
    "Blue", "Red", "Green", "Gold",
    "Coop", "No",  "No",    "No",
};

int TeamBoxes[TEAMCOUNT] = 
{
    "H_BLUBOX", "H_REDBOX", "H_GRNBOX", "H_GLDBOX",
    "H_ALLBOX", "H_ALLBOX", "H_ALLBOX", "H_ALLBOX",
};

int TeamColors[TEAMCOUNT] = 
{
    CR_LIGHTBLUE, CR_RED, CR_GREEN, CR_GOLD,
    CR_WHITE, CR_WHITE, CR_WHITE, CR_WHITE,
};

int TeamLoseColors[TEAMCOUNT] = 
{
    CR_BLUE, CR_DARKRED, CR_DARKGREEN, CR_BROWN,
    CR_DARKGREY, CR_DARKGREY, CR_DARKGREY, CR_DARKGREY,
};

int TeamColors2[TEAMCOUNT] = 
{
    "\cn", "\cg", "\cd", "\ck",
    "\cj", "",    "",    "",
};

#define CHOICES_X 7
#define CHOICES_Y 4

int HangmanPickChoices[CHOICES_Y][CHOICES_X] = 
{
    {'A', 'B', 'C', 'D', 'E', 'F', 'G'},
    {'H', 'I', 'J', 'K', 'L', 'M', 'N'},
    {'O', 'P', 'Q', 'R', 'S', 'T', 'U'},
    {' ', 'V', 'W', 'X', 'Y', 'Z', ' '},
};

int ValidCharacters[256] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
