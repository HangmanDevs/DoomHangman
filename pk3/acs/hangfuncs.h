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
