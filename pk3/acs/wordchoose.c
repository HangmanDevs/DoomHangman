#include "zcommon.acs"

#include "commonFuncs.h"
#include "stralloc.h"

#include "hangdefs.h"
#include "hangwords.h"
#include "hangfuncs.h"

#library "wordchoose"

script HANGMAN_WORDOPEN open
{
    int seedVal = abs(GetCVar("hangman_rngseed"));
    int i;

    for (i = 0; i < TEAMCOUNT; i++) { setHangmanWord(i, ""); }

    Print(s:"Seeding RNG (", d:seedVal, s:")...");
    for (i = 0; i < seedVal; i++)
    {
        random(0, -1);
        if (i % 5000 == 0) { Delay(1); }
    }
    Print(s:"done.");

    ACS_ExecuteWithResult(HANGMAN_CHOOSEWORD);
}

script HANGMAN_CHOOSEWORD (void)
{
    int skill = GameSkill();
    int choice = HangmanWordLists[skill][random(0, WORDCOUNT-1)];

    Print(s:"The word is ", s:choice);
    setRNGSeed();
}
