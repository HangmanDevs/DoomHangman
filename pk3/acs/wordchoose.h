script HANGMAN_WORDOPEN open
{
    int seedVal = abs(GetCVar("hangman_rngseed"));
    int i;

    IsServer = 1;

    if (GetCVar("hangman_guesses") == 0)
    {
        ConsoleCommand("set hangman_guesses 8");
        ConsoleCommand("archivecvar hangman_guesses");
    }

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
    int i;

    for (i = 0; i < TEAMCOUNT; i++)
    {
        clearPickedChars(i);
        setHangmanWord(i, choice);
    }
    setRNGSeed();
}

script 777 (void)
{
    int i;
    for (i = 0; i < TEAMCOUNT; i++) { Print(s:getString(HangmanWords[i])); }

    Print(d:getHangmanChar(0, 1), s:", ", c:getHangmanChar(0, 1));
}
