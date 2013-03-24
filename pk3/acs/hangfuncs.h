function int setHangmanWord(int team, int word)
{
    int newWord, prevWord = HangmanWords[team];

    if (prevWord != 0) { freeString(prevWord); }

    newWord = addString(word);
    HangmanWords[team] = newWord;
    return newWord;
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
