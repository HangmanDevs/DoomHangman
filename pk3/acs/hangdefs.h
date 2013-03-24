#define HANGMAN_WORDOPEN        481
#define HANGMAN_CHOOSEWORD      482
#define SETCOLORS 900

global int 32:HangmanWords[];
global int 33:HangmanPickedChars[];

script SETCOLORS (int r, int g, int b) clientside {
	for(int s = 0; s < 32767; s++)
	{
		Sector_SetColor(s, r, g, b);
	}
}
