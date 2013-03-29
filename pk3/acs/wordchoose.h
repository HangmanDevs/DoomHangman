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

    ConsoleCommand("set sv_useteamstartsindm 1");

    if (!(GetCVar("survival") || (isLMS() && isTeamGame())))
    {
        SetHudSize(640, 480, 0);
        SetFont("BIGFONT");
        HudMessage(s:"Yo what the hell is going on."; HUDMSG_PLAIN, 901,
            CR_BRICK, 320.4, 80.1, 5.0, 1.0);

        if (isCoop())
        {
            ConsoleCommand("set survival 1");
            HudMessage(s:"Switched to survival."; HUDMSG_PLAIN|HUDMSG_LOG, 902,
                CR_YELLOW, 320.4, 100.1, 5.0, 1.0);
        }
        else
        {
            ConsoleCommand("set teamlms 1");
            HudMessage(s:"Switched to TLMS."; HUDMSG_PLAIN|HUDMSG_LOG, 902,
                CR_YELLOW, 320.4, 100.1, 5.0, 1.0);
        }

        HudMessage(s:"Now restart the game."; HUDMSG_PLAIN|HUDMSG_LOG, 903,
                CR_WHITE, 320.4, 120.1, 5.0, 1.0);

        terminate;
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
    int choice;
    int i, j;
    int count, ocount;

    choice = HangmanWordLists[skill][random(0, WORDCOUNT-1)];

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


script HANGMAN_ENTER   enter   { ACS_ExecuteWithResult(HANGMAN_SPAWN, 0); }
script HANGMAN_RESPAWN respawn { ACS_ExecuteWithResult(HANGMAN_SPAWN, 1); }

script HANGMAN_SPAWN (int respawning)
{
    int pln = PlayerNumber();
    int pltid = defaultTID(-1);

    PlayerTIDs[pln] = pltid;
}

script HANGMAN_DEATH death
{
    oneTeamReveal();
}

script HANGMAN_DISCONNECT (int pln) disconnect
{
    oneTeamReveal();
}
