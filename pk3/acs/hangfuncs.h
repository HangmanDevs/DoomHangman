function int setHangmanWord(int team, int word)
{
    int newWord, prevWord = HangmanWords[team];
    int i, j, len = StrLen(word);

    if (prevWord != 0) { freeString(prevWord); }

    newWord = addString(word);
    HangmanWords[team] = newWord;
    setGuessesLeft(team, GetCVar("hangman_guesses"));
    clearPickedChars(team);

    for (i = 0; i < len; i++)
    {
        j = GetChar(word, i);
        if (j == 32) { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, j, team); }
        else { ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, i, -2, team); }
    }
    ACS_ExecuteAlways(HANGMAN_REVEALLETTER, 0, len, -3);
    WordLengths[team] = len;

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

    if (!isCoop() && IsServer != 1)
    {
        if (PlayerIsSpectator(cpln) && team != -1 && chr >= 0) { terminate; }
        if (team != GetPlayerInfo(cpln, PLAYERINFO_TEAM)) { terminate; }
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
    pick = lower(pick);

    PrintBold(s:"Team ", d:team, s:" picking char \'", c:pick, s:"\'");

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
    pick = lower(pick);
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
    pick = lower(pick);

    while (1)
    {
        chr = getHangmanChar(team, i++);
        chr = lower(chr);
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

function int hangmanWordLen(int team)
{
    return WordLengths[team];
}
