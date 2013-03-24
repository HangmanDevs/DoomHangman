script HANGMAN_HUD open clientside
{
    int pln = ConsolePlayerNumber();
    int team, i, wordoffset, k, wordlen, chr;
    SetHudSize(640, 480, 1);

    if (isCoop())
    {
        SetFont("H_BOXHED");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4829, CR_UNTRANSLATED,
                    60.4, 104.1, 0);

        SetFont("H_ALLBOX");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4839, CR_UNTRANSLATED,
                    60.4, 120.1, 0);
    }
    else if (isTeamgame())
    {
        SetFont("H_BOXHED");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4829, CR_UNTRANSLATED,
                    60.4, 104.1, 0);
        
        for (i = 0; i < min(4, GetCVar("sv_maxteams")); i++)
        {
            SetFont(TeamBoxes[i]);
            HudMessage(s:"A"; HUDMSG_PLAIN, 4839 + (10*i), CR_UNTRANSLATED,
                        60.4, 120.1 + (32.0 * i), 0);
        }
    }
    
    while (1)
    {
        team = GetPlayerInfo(pln, PLAYERINFO_TEAM);
        wordlen = hangmanWordLen(team);
        SetHudSize(640, 480, 1);

        if (isCoop())
        {
            SetFont("BIGFONT");
            HudMessage(d:HangmanGuessesLeft[team]; HUDMSG_PLAIN, 4831, CR_WHITE,
                        84.4, 136.0, 0);
        }
        else if (isTeamgame())
        {
            for (i = 0; i < min(4, GetCVar("sv_maxteams")); i++)
            {
                SetFont("BIGFONT");
                HudMessage(d:HangmanGuessesLeft[i]; HUDMSG_PLAIN, 4831 + (10*i), TeamColors[i],
                            84.4, 136.0 + (32.0 * i), 0);
            }
        }

        wordoffset = 68.0 - (wordlen * 8.0);
        for (i = 0; i < wordlen; i++)
        {
            chr = KnownLetters[i]-1;
            SetFont("BIGFONT");

            if (chr == -2)
            {
                HudMessage(s:"_"; HUDMSG_PLAIN, 3800+i, TeamColors[team], wordoffset + (16.0 * i), 100.2, 0);
            }
            else
            {
                HudMessage(c:chr; HUDMSG_PLAIN, 3800+i, TeamColors[team], wordoffset + (16.0 * i), 100.2, 0);
            }
        }

        if (Timer()%35 == 0) { Log(d:team, s:"'s word len is ", d:wordlen); }
        Delay(1);
    }
}
