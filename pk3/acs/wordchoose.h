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
    int i, j;
    int count, ocount;

    for (i = 0; i < TEAMCOUNT; i++)
    {
        setHangmanWord(i, choice);
    }
    setRNGSeed();

    while (1)
    {
        ocount = count;
        count = PlayerCount();

        if (count > ocount || j % 70 == 0)
        {
            for (i = 0; i < TEAMCOUNT; i++) { syncWord(i); }
            j = 0;
        }

        j++;
        Delay(1);
    }
}

script 777 (void)
{
    int i;
    for (i = 0; i < TEAMCOUNT; i++) { Print(s:getString(HangmanWords[i])); }

    Print(d:getHangmanChar(0, 1), s:", ", c:getHangmanChar(0, 1));
}

script HANGMAN_PICK (int pick) {
	int team = GetPlayerInfo(PlayerNumber());
	if(!charPicked(team, pick) {
		if(guess(team, pick) {
			ACS_ExecuteAlways(HANGMAN_PICK_SUCCESS, 0, team, pick);
		}
		else {
			ACS_ExecuteAlways(HANGMAN_PICK_FAIL, 0, team, pick);
		}
	}
}