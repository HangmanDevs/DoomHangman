script HANGMAN_PICK (int pick) net
{
    int pln = PlayerNumber();
    int team = getHangmanTeam(PlayerNumber());

    if (!HangmanOn)
    {
        SetHudSize(640,480, 1);
        SetFont("BIGFONT");
        HudMessage(s:"Wait for the game to start!"; HUDMSG_FADEOUT, 9100, CR_RED,
                320.4, 160.2, 1.0, 0.5);
    }

    if (!charPicked(team, pick))
    {
        if (guess(team, pick)) { ACS_ExecuteAlways(HANGMAN_PICK_SUCCESS, 0, team, pick); }
        else { ACS_ExecuteAlways(HANGMAN_PICK_FAIL, 0, team, pick); }
    }
    else
    {
        SetHudSize(640,480, 1);
        SetFont("BIGFONT");
        HudMessage(s:"\cf", c:pick, s:"\c- has already been picked!"; HUDMSG_FADEOUT, 9100, CR_RED,
                320.4, 160.2, 1.0, 0.5);
    }
}

script HANGMAN_PICKMENU (void)
{
    int pln = PlayerNumber();

    if (!HangmanOn)
    {
        SetHudSize(640,480, 1);
        SetFont("BIGFONT");
        HudMessage(s:"Wait for the game to start!"; HUDMSG_FADEOUT, 9100, CR_RED,
                320.4, 160.2, 1.0, 0.5);
    }

    if (InPickMenu[pln]) { terminate; }
    InPickMenu[pln] = 1;

    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    SetActorVelocity(0, 0,0,0, 0,0);

    ACS_ExecuteAlways(HANGMAN_PICKMENU_CLIENT, 0);

    while (InPickMenu[pln]) { Delay(1); }
    SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
}

script HANGMAN_ENDMENU (void) net
{
    int pln = PlayerNumber();

    if (!InPickMenu[pln]) { terminate; }

    InPickMenu[pln] = 0;
    GiveInventory("EndMenu", 1);
    Delay(4);
    TakeInventory("EndMenu", 1);
}

script HANGMAN_PICKMENU_CLIENT (void) clientside
{
    int pln = PlayerNumber();
    if (pln != ConsolePlayerNumber()) { terminate; }

    int team = getHangmanTeam(pln);

    if (HangmanGuessesLeft[team] <= 0)
    {
        ConsoleCommand(StrParam(s:"puke -", d:HANGMAN_ENDMENU));
        terminate;
    }

    int choiceX, choiceY, altChoiceX, choiceColor, choice;
    int dX, dY;
    int x, y, baseX = itof(320 - ((32*(CHOICES_X-1))/2)) + 0.4;

    choiceX = (CHOICES_X-1)/2;
    choiceY = (CHOICES_Y-1)/2;

    SetHudSize(640, 480, 0);
    InPickMenu[pln] = 1;

    while (!CheckInventory("EndMenu"))
    {
        drawWord(320, 280, 7600, 1.0);

        for (x = 0; x < CHOICES_X; x++)
        {
            for (y = 0; y < CHOICES_Y; y++)
            {
                choice = HangmanPickChoices[y][x];
                SetFont("BIGFONT");

                if (HangmanGuessesLeft[team] <= 0)
                {
                    choiceColor = CR_DARKRED;
                }
                if (x == choiceX && y == choiceY)
                {
                    if (charPicked(team, choice)) { choiceColor = CR_BROWN; }
                    else { choiceColor = CR_YELLOW; }
                }
                else
                {
                    if (charPicked(team, choice)) { choiceColor = CR_DARKGREY; }
                    else { choiceColor = CR_WHITE; }
                }

                HudMessage(c:HangmanPickChoices[y][x]; HUDMSG_FADEOUT, 7800+(x*CHOICES_Y)+y, choiceColor,
                        baseX + (x * 32.0), 300.1 + (y * 24.0), 0.25, 0.5);
            }
        }

        if (HangmanGuessesLeft[team] <= 0)
        {
            ConsoleCommand(StrParam(s:"puke -", d:HANGMAN_ENDMENU));
            break; 
        }

        SetFont("SMALLFONT");
        HudMessage(s:"Hit \cf", k:"+use", s:"\c- to pick a letter\n\nHit \cf", k:"+jump", s:"\c- to exit"; HUDMSG_FADEOUT, 7900, CR_GREEN,
                        320.4, 400.1, 0.25, 0.5);

        if (keyPressed(BT_JUMP))
        {
            ConsoleCommand(StrParam(s:"puke -", d:HANGMAN_ENDMENU));
            break; 
        }

        if (keyPressed(BT_USE))
        {
            ConsoleCommand(StrParam(s:"puke -", d:HANGMAN_PICK, s:" ", d:HangmanPickChoices[choiceY][choiceX]));
        }
    
        dX  = keyPressed_any(BT_MOVERIGHT | BT_RIGHT);
        dX -= keyPressed_any(BT_MOVELEFT  | BT_LEFT);

        dY  = keyPressed_any(BT_BACK    | BT_LOOKDOWN);
        dY -= keyPressed_any(BT_FORWARD | BT_LOOKUP);

        if (dX != 0 || dY != 0)
        {
            while (1)
            {
                choiceX += dX; choiceY += dY;
                choiceX = mod(choiceX, CHOICES_X); choiceY = mod(choiceY, CHOICES_Y);
                if (HangmanPickChoices[choiceY][choiceX] != ' ') { break; }
            }
        }
        Delay(1);
    }

    InPickMenu[pln] = 0;
}
