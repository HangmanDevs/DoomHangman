#!/usr/bin/env python3

import os
import string
import random

wordFiles = {
    "0": "wordlists/skill0.txt",
    "1": "wordlists/skill1.txt",
    "2": "wordlists/skill2.txt",
    "3": "wordlists/skill3.txt",
    "4": "wordlists/skill4.txt",
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

        for char in nextWord:
            if char not in string.ascii_letters:
                continue


        while True:
            choice = "invalid"
            prompt = "\"{}\" [{}]: ".format(nextWord, "".join(sorted(wordFiles)) + "m")

            while choice not in wordFiles and (choice and choice != "m"):
                choice = input(prompt).lower()

            if choice == "m":
                nextWord = input("change to: ")
                continue

            if choice:
                addWord(nextWord, wordFiles[choice])
                print("added \"{}\" to \"{}\"".format(nextWord, wordFiles[choice]))

            break

except EOFError:
    pass
