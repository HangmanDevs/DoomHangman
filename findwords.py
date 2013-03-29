#!/usr/bin/env python3

import os
import random

wordFiles = {
    "0": "wordlists/skill0.txt",
    "1": "wordlists/skill1.txt",
    "2": "wordlists/skill2.txt",
    "3": "wordlists/skill3.txt",
    "4": "wordlists/skill4.txt",
    "S": "wordlists/super.txt",
    "s": "wordlists/super.txt",
}

dictDir = "/usr/share/dict"

def addWord(word, file):
    fd = open(file, "r+")
    text = fd.read()
    
    if text[-1] != "\n": fd.write("\n")
    fd.write("{}\n".format(word))
    fd.close()

wordsToChoose = set()

for dictFile in os.listdir(dictDir):
    dictWords = set(open("{}/{}".format(dictDir, dictFile)).read().split("\n"))
    wordsToChoose |= dictWords

wordsToChooseL = list(wordsToChoose)

try:
    while True:
        nextWord = random.choice(wordsToChooseL)

        prompt = "\"{}\" [{}]: ".format(nextWord, "".join(sorted(wordFiles)))
        choice = "invalid"

        while choice not in wordFiles and choice:
            choice = input(prompt)

        if choice:
            addWord(nextWord, wordFiles[choice])

except EOFError:
    pass
