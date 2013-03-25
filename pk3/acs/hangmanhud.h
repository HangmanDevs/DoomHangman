script HANGMAN_HUD open clientside
{
    int pln = ConsolePlayerNumber();
    int team, i, wordoffset, k, wordlen, chr;
    SetHudSize(640, 480, 1);

    if (isCoop())
    {
        SetFont("H_BOXHED");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4829, CR_UNTRANSLATED,
                    HUD_CENTERX+0.4, HUD_CORNERY+0.1, 0);

        SetFont("H_ALLBOX");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4839, CR_UNTRANSLATED,
                    HUD_CENTERX+0.4, HUD_CORNERY+16.1, 0);
    }
    else if (isTeamgame())
    {
        SetFont("H_BOXHED");
        HudMessage(s:"A"; HUDMSG_PLAIN, 4829, CR_UNTRANSLATED,
                    HUD_CENTERX+0.4, HUD_CORNERY+0.1, 0);
        
        for (i = 0; i < min(4, GetCVar("sv_maxteams")); i++)
        {
            SetFont(TeamBoxes[i]);
            HudMessage(s:"A"; HUDMSG_PLAIN, 4839 + (10*i), CR_UNTRANSLATED,
                        HUD_CENTERX+0.4, HUD_CORNERY+16.1 + (32.0*i), 0);
        }
    }
    
    while (1)
    {
        team = getHangmanTeam(pln);
        SetHudSize(640, 480, 1);

        if (isCoop())
        {
            SetFont("BIGFONT");
            if (WinningTeam == team)
            {
                HudMessage(s:"WIN"; HUDMSG_PLAIN, 4831, CR_WHITE,
                            HUD_CENTERX+23.4, HUD_CORNERY+32.0, 0);
            }
            else
            {
                HudMessage(d:HangmanGuessesLeft[team]; HUDMSG_PLAIN, 4831, CR_WHITE,
                            HUD_CENTERX+23.4, HUD_CORNERY+32.0, 0);
            }
        }
        else if (isTeamgame())
        {
            for (i = 0; i < min(4, GetCVar("sv_maxteams")); i++)
            {
                SetFont("BIGFONT");
                if (WinningTeam == i)
                {
                    HudMessage(s:"WIN"; HUDMSG_PLAIN, 4831 + (10*i), TeamColors[i],
                                HUD_CENTERX+23.4, HUD_CORNERY+32.0+(32.0*i), 0);
                }
                else
                {
                    HudMessage(d:HangmanGuessesLeft[i]; HUDMSG_PLAIN, 4831 + (10*i), TeamColors[i],
                                HUD_CENTERX+23.4, HUD_CORNERY+32.0+(32.0*i), 0);
                }
            }
        }

        if (!InPickMenu[pln]) { drawWord(ftoi(HUD_CENTERX), ftoi(HUD_CORNERY)-8, 3800, 0.25); }

        Delay(1);
    }
}
