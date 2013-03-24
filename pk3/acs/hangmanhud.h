script HANGMAN_HUD open clientside
{
    int pln = PlayerNumber();
    int team, i;
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
        team = GetPlayerInfo(-1, PLAYERINFO_TEAM);
        SetHudSize(640, 480, 1);

        if (isCoop())
        {
            SetFont("BIGFONT");
            HudMessage(d:HangmanGuessesLeft[4]; HUDMSG_PLAIN, 4831, CR_WHITE,
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

        Delay(1);
    }
}
