script HANGMAN_WORDOPEN open
{
    int seedVal = abs(GetCVar("hangman_rngseed"));
    int i;

    IsServer = 1;
    setGameState(0, -1);

    if (GetCVar("hangman_guesses") == 0)
    {
        ConsoleCommand("set hangman_guesses 8");
        ConsoleCommand("archivecvar hangman_guesses");
    }

    if (!(GetCVar("survival") || (isLMS() && isTeamGame())))
    {
        SetHudSize(640, 480, 0);
        SetFont("BIGFONT");
        HudMessage(s:"Yo what the hell is going on."; HUDMSG_PLAIN, 901,
            CR_BRICK, 320.4, 120.1, 5.0, 1.0);

        if (isCoop())
        {
            ConsoleCommand("set survival 1");
            HudMessage(s:"Switching to survival..."; HUDMSG_PLAIN, 902,
                CR_YELLOW, 320.4, 140.1, 5.0, 1.0);
        }
        else
        {
            ConsoleCommand("set teamlms 1");
            HudMessage(s:"Switching to TLMS..."; HUDMSG_PLAIN, 902,
                CR_YELLOW, 320.4, 140.1, 5.0, 1.0);
        }
    }


    for (i = 0; i < TEAMCOUNT; i++) { setHangmanWord(i, ""); }

    Print(s:"Seeding RNG (", d:seedVal, s:")...");
    for (i = 0; i < seedVal; i++)
    {
        random(0, -1);
        if (i % 5000 == 4999) { Delay(1); }
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
    setGameState(1, -1);

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
