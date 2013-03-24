function int setHangmanWord(int team, int word)
{
    int newWord, prevWord = HangmanWords[team];
    int i, j, len = StrLen(word);

    if (prevWord != 0) { freeString(prevWord); }

    newWord = addString(word);
    HangmanWords[team] = newWord;
    setGuessesLeft(team, GetCVar("hangman_guesses"));

    for (i = 0; i < len; i++)
    {
        j = GetChar(word, i);
        if (j == 32) { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, j, -1); }
        else { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, -2, -1); }
    }
    ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, len, -3);

    return newWord;
}

function void setGuessesLeft(int team, int guessCount)
{
    HangmanGuessesLeft[team] = guessCount;
    ACS_ExecuteAlways(HANGMAN_SETGUESSES, 0, team, guessCount);
}

script HANGMAN_REVEALLETTER (int pos, int chr, int team) clientside
{
    int cpln = ConsolePlayerNumber();

    if (!isCoop() && IsServer != 1)
    {
        if (PlayerIsSpectator(cpln) && team != -1 && chr >= -1) { terminate; }
        if (team != GetPlayerInfo(cpln, PLAYERINFO_TEAM)) { terminate; }
    }
    KnownLetters[pos] = chr+1;
}

script HANGMAN_SETGUESSES (int team, int guesses) clientside
{
    if (IsServer == 1) { terminate; }
    HangmanGuessesLeft[team] = guesses;
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
    onOff = !!onOff;
    if (pick < 0 || pick > 255)
    {
        Log(s:"** ERROR **\nTried to set char ", d:pick, s:" to ", d:onOff, s:" on team ", d:team, s:", which is invalid\n** ERROR **");
        return;
    }
    HangmanPickedChars[(team*256)+pick] = onOff;
}

function int charPicked(int team, int pick)
{
    if (pick < 0 || pick > 255)
    {
        Log(s:"** ERROR **\nTried to get char ", d:pick, s:" on team ", d:team, s:", which is invalid\n** ERROR **");
        return -1;
    }
    return HangmanPickedChars[(team*256)+pick];
}

function int getHangmanChar(int team, int index)
{
    int indexStart = HangmanWords[team];
    if (indexStart == 0) { return -1; }

    int wordlen = stringLength(indexStart);
    if (index >= wordlen || index < 0) { return -1; }

    return strings[indexStart+index];
}

function int charInWord(int team, int pick)
{
    int ret, chr, i = 0;
    while (1)
    {
        chr = getHangmanChar(team, i++);
        if (chr == -1)   { break; }
        if (chr == pick) { return 1; }
    }
    return 0;
}

function int guess(int team, int pick)
{
    pickChar(team, pick, 1);
    int ret = charInWord(team, pick);
    if (!ret) { HangmanGuessesLeft[team]--; }
    return ret;
}
