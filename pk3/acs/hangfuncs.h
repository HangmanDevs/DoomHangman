function int getHangmanTeam(int pln)
{
    if (PlayerIsSpectator(pln) || isCoop()) { return 4; }
    return GetPlayerInfo(pln, PLAYERINFO_TEAM);
}

function int setHangmanWord(int team, int word)
{
    int newWord, prevWord = HangmanWords[team];
    int i, j, len = StrLen(word);

    if (prevWord != 0) { freeString(prevWord); }

    newWord = addString(word);
    HangmanWords[team] = newWord;
    clearPickedChars(team);
    setGuessesLeft(team, GetCVar("hangman_guesses"));

    for (i = 0; i < len; i++)
    {
        j = GetChar(word, i);
        if (j == 32) { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, j, team); }
        else { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, -2, team); }
    }
    ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, len, -3);
    WordLengths[team] = len;

    if (ThingCountName("HangmanNoGuesses", 0) > 0) { setGameState2(1, -1, 1); }
    else { setGameState2(1, -1, -1); }

    return newWord;
}

function void syncWord(int team)
{
    int i, j;
    int len = hangmanWordLen(team);

    for (i = 0; i < len; i++)
    {
        j = getHangmanChar(team, i);

        if (j == 32 || charPicked(team, j))
        {
            ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, j, team);
        }
        else
        {
            ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, -12, team);
        }
    }
    ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, len, -13, team);
    ACS_ExecuteAlways(HANGMAN_SETGUESSES, 0, team, HangmanGuessesLeft[team]);
    ACS_ExecuteAlways(HANGMAN_SETGAMESTATE, 0, HangmanOn, WinningTeam);

    for (i = 0; i < 256; i++)
    {
        if (charPicked(team, i)) { ACS_ExecuteAlways(HANGMAN_SETPICKED, 0, team, i, 1); }
    }
}

function void setGuessesLeft(int team, int guessCount)
{
    HangmanGuessesLeft[team] = guessCount;
    ACS_ExecuteAlways(HANGMAN_SETGUESSES, 0, team, guessCount);
}

script HANGMAN_REVEALLETTER (int pos, int chr, int team) clientside
{
    int cpln = ConsolePlayerNumber();
    chr++;

    if (!isCoop() && team != 4 && IsServer != 1)
    {
        if (PlayerIsSpectator(cpln) && team != -1 && chr >= 0) { terminate; }
        if (team != getHangmanTeam(cpln)) { terminate; }
    }

    //Log(s:"chr for ", d:team, s:" is ", d:chr);

    if (chr == -11 || chr == -12)
    {
        if (KnownLetters[pos] <= 0)
        {
            if (chr == -12 && IsServer != 1) { WordLengths[team] = pos; }
            KnownLetters[pos] = chr+10;
        }
    }
    else
    {
        if (chr == -2 && IsServer != 1) { WordLengths[team] = pos; }
        KnownLetters[pos] = chr;
    }
}

script HANGMAN_SETGUESSES (int team, int guesses) clientside
{
    if (IsServer == 1) { terminate; }
    HangmanGuessesLeft[team] = guesses;
}

script HANGMAN_SETPICKED (int team, int chr, int picked) clientside
{
    picked = !!picked;
    HangmanPickedChars[(team*256)+chr] = picked;
}

function int setRNGSeed(void)
{
    int i = random(0, 65535);
    saveCVar("hangman_rngseed", i);
    return i;
}

function void clearPickedChars(int team)
{
    int i;
    for (i = 0; i < 256; i++) { HangmanPickedChars[(team*256)+i] = 0; }
}

function void pickChar(int team, int pick, int onOff)
{
    int i, wordlen;

    onOff = !!onOff;
    pick = lower(pick);

    //PrintBold(s:"Team ", d:team, s:" picking char \'", c:pick, s:"\'");

    if (pick < 0 || pick > 255)
    {
        Log(s:"** ERROR **\nTried to set char ", d:pick, s:" to ", d:onOff, s:" on team ", d:team, s:", which is invalid\n** ERROR **");
        return;
    }
    HangmanPickedChars[(team*256)+pick] = onOff;
    ACS_ExecuteAlways(HANGMAN_SETPICKED, 0, team, pick, 1);

    wordlen = hangmanWordLen(team);
    for (i = 0; i < wordlen; i++)
    {
        if (lower(getHangmanChar(team, i)) == lower(pick))
        {
            ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, pick, team);
        }
    }
}

function int charPicked(int team, int pick)
{
    if (pick == 32) { return 1; }
    if (pick < 0 || pick > 255)
    {
        Log(s:"** ERROR **\nTried to get char ", d:pick, s:" on team ", d:team, s:", which is invalid\n** ERROR **");
        return -1;
    }

    if (!ValidCharacters[pick]) { return -1; }

    pick = lower(pick);
    return HangmanPickedChars[(team*256)+pick];
}

function int getHangmanChar(int team, int index)
{
    int indexStart = HangmanWords[team];
    if (indexStart == 0) { return -1; }

    int wordlen = WordLengths[team];
    if (index >= wordlen || index < 0) { return -1; }

    return strings[indexStart+index];
}

function int charInWord(int team, int pick)
{
    int ret, chr, i = 0;
    pick = lower(pick);

    if (!ValidCharacters[pick]) { return -1; }

    while (1)
    {
        chr = getHangmanChar(team, i++);
        chr = lower(chr);
        if (chr <= -1)   { break; }
        if (chr == pick) { return 1; }
    }
    return 0;
}

function int revealAtPos(int team, int pos)
{
    int chr = getHangmanChar(team, pos);

    HangmanPickedChars[(team*256)+chr] = 1;
    ACS_ExecuteAlways(HANGMAN_SETPICKED, 0, team, chr, 1);
    ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, pos, chr, team);
    return chr;
}

function void revealWord(int team)
{
    int j, wordlen = hangmanWordLen(team);
    for (j = 0; j < wordlen; j++) { revealAtPos(team, j); }
}

function int guess(int team, int pick)
{
    pickChar(team, pick, 1);
    int ret = charInWord(team, pick);

    if (ret == 0 && !HangmanNoGuesses)
    {
        HangmanGuessesLeft[team]--;
        ACS_ExecuteAlways(HANGMAN_SETGUESSES, 0, team, HangmanGuessesLeft[team]);
    }
    return ret;
}

function int hangmanWordLen(int team)
{
    return WordLengths[team];
}

function void drawWord(int centerX, int centerY, int id, int duration)
{
    int team = getHangmanTeam(ConsolePlayerNumber());
    int wordlen = hangmanWordLen(team);
    int wordoffset = itof(centerX) - ((wordlen-1) * 8.0);
    int chr, i;

    centerY = itof(centerY) + 0.2;

    for (i = 0; i < wordlen; i++)
    {
        chr = KnownLetters[i]-1;
        SetFont("BIGFONT");

        if (chr == -2) { HudMessage(s:"_"; HUDMSG_PLAIN, id+i, TeamColors[team], wordoffset + (16.0 * i), centerY, duration); }
        else { HudMessage(c:chr; HUDMSG_PLAIN, id+i, TeamColors[team], wordoffset + (16.0 * i), centerY, duration); }
    }
}

function int completedWord(int team)
{
    int len = hangmanWordLen(team);
    int i, chr;

    for (i = 0; i < len; i++)
    {
        chr = getHangmanChar(team, i);
        if (!charPicked(team, chr)) { return 0; }
    }

    return 1;
}

function void setWinner(int team)
{
    int i, j, k, wordlen;
    int alertteams = min(GetCVar("sv_maxteams"), TEAMCOUNT);

    WinningTeam = team;

    if (team > -1)
    {
        if (alertteams < 4) { revealWord(4); }
        for (i = 0; i < alertteams; i++) { revealWord(i); }
    }
}

function void setGameState(int onOff, int team)
{
    setGameState2(onOff, team, 0);
}

function void setGameState2(int onOff, int team, int noGuesses)
{
    HangmanOn = onOff;
    setWinner(team);
    if (noGuesses == -1) { HangmanNoGuesses = 0; }
    if (noGuesses ==  1) { HangmanNoGuesses = 1; }

    ACS_ExecuteAlways(HANGMAN_SETGAMESTATE, 0, onOff, team, noGuesses);
}

script HANGMAN_SETGAMESTATE (int onOff, int team, int noGuesses) clientside
{
    if (IsServer != 1)
    {
        HangmanOn   = onOff;
        WinningTeam = team;

        if (noGuesses == -1) { HangmanNoGuesses = 0; }
        if (noGuesses ==  1) { HangmanNoGuesses = 1; }
    }
}

function int oneTeamReveal(void)
{
    int alertteams = min(TEAMCOUNT, GetCVar("sv_maxteams"));
    int i, j, someoneAlive = 0, teamField = 0, teamsLeft;

    teamsLeft = 0;
    for (i = 0; i < PLAYERMAX; i++)
    {
        if (!PlayerInGame(i)) { continue; }
        if (GetActorProperty(PlayerTIDs[i], APROP_Health) <= 0) { continue; }
        someoneAlive = 1;
        j = GetPlayerInfo(i, PLAYERINFO_TEAM);

        if (HangmanGuessesLeft[j] > 0)
        {
            if (!(teamField & (1 << j))) { teamsLeft++; }
            teamField |= (1 << j);
        }
    }
    
    if (isCoop()) { if (!someoneAlive || HangmanGuessesLeft[4] <= 0) { revealWord(4); } }
    else if (teamsLeft <= 1)
    {
        for (i = 0; i < alertteams; i++) { revealWord(i); }
        return 1;
    }

    return 0;
}
