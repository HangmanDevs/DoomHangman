#define HANGMAN_WORDOPEN        481
#define HANGMAN_CHOOSEWORD      482
#define HANGMAN_REVEALLETTER    483
#define HANGMAN_SETGUESSES      484

#define HANGMAN_HUD             584
#define SETCOLORS 900

global int 32:HangmanWords[];
global int 33:HangmanPickedChars[];
global int 34:HangmanGuessesLeft[];
global int 35:KnownLetters[];
global int 36:WordLengths[];

int IsServer = -1;

script SETCOLORS (int r, int g, int b) clientside {
	for(int s = 0; s < 32767; s++)
	{
		Sector_SetColor(s, r, g, b);
	}
}

int TeamBoxes[TEAMCOUNT] = 
{
    "H_BLUBOX", "H_REDBOX", "H_GRNBOX", "H_GLDBOX",
    "H_ALLBOX", "H_ALLBOX", "H_ALLBOX", "H_ALLBOX",
};

int TeamColors[TEAMCOUNT] = 
{
    CR_LIGHTBLUE, CR_BRICK, CR_GREEN, CR_GOLD,
    CR_WHITE, CR_WHITE, CR_WHITE, CR_WHITE,
};
