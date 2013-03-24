#include "zcommon.acs"

#include "commonFuncs.h"

#include "hangdefs.h"
#include "hangwords.h"
#include "hangfuncs.h"

script HANGMAN_WORDOPEN open
{
    int seedVal = GetCVar("hangman_rngseed");
    int i;

    Print(s:"Seeding RNG...");
    for (i = 0; i < seedVal; i++)
    {
        random(0, -1);
        if (i % 1000 == 0) { Delay(1); }
    }
    Print(s:"done.");

    ACS_ExecuteWithResult(HANGMAN_CHOOSEWORD);
}

script HANGMAN_CHOOSEWORD (void)
{
    int skill = GameSkill();
}
