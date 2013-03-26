#!/usr/bin/env python3

import os

templateString = """\
#define WORDCOUNT {wc}
#define SUPERWORDCOUNT {swc}

int HangmanWordLists[SKILLCOUNT][WORDCOUNT] = 
{wl};

int HangmanSuperWords[SUPERWORDCOUNT] = 
{swl};"""

WORDDIR = "wordlists"
wordFiles = sorted(filter(lambda x: x.startswith("skill"), os.listdir(WORDDIR)))
wordLists = []
wordStrs = []
formatDict = {}

for i, file in enumerate(wordFiles):
    file = WORDDIR + os.sep + file
    try:
        words = [i for i in open(file).readlines()]
        word2 = []

        for word in words:
            tmp = word.partition("//")[0].strip()
            if tmp: word2.append(tmp)

        words = sorted(word2)
        wordLists.append(words)

    except IOError:
        wordLists.append([])

wordcount = max(len(i) for i in wordLists)

for words in wordLists:
    tmp = ["    {\n"]

    if len(words) == 0:
        words.extend(["filler"] * (wordcount - len(words)))
    else:
        words *= 1 + (wordcount // len(words))
        words = words[:wordcount]

    for i, word in enumerate(words):
        if (i % 8 == 0): tmp2 = "        \"{}\", "
        elif (i % 8 == 7): tmp2 = "\"{}\",\n"
        else: tmp2 = "\"{}\", "

        tmp2 = tmp2.format(word)

        tmp.append(tmp2)

    if tmp[-1][-1] != "\n": tmp.append("\n")
    tmp.append("    },\n")

    wordStrs.append("".join(tmp))


try:
    superwords = [i.strip() for i in open("wordlists/super.txt").readlines()]
    superwords = sorted(superwords)
except IOError:
    superwords = []

tmp = []

for i, word in enumerate(superwords):
    if (i % 8 == 0): tmp2 = "    \"{}\", "
    elif (i % 8 == 7): tmp2 = "\"{}\",\n"
    else: tmp2 = "\"{}\", "

    tmp2 = tmp2.format(word)

    tmp.append(tmp2)

if tmp[-1][-1] != "\n": tmp.append("\n")

superWordStrs = "".join(tmp)

formatDict["wc"]    = wordcount
formatDict["wl"]    = "{{\n{}}}".format("\n".join(wordStrs))
formatDict["swc"]   = len(superwords)
formatDict["swl"]   = "{{\n{}}}".format(superWordStrs)

print(templateString.format(**formatDict))
