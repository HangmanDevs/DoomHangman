# HANGMAN

## Maps
HM01: Hangman!

HM02-6: Hangman Survival!

HM07-11: Team Hangman!

## Credits

Synert: ACS, meh.mid, maps 1,2,3,5,6,7 and 8

Philnemba: Map 4

Ijon Tichy: generating about 15,000 words for me, helping with ACS, idea for HM08, HM11

Konda: suggesting LOL I'M TYPING, helping with ACS, HM10, Decorate, and a truckload of sprites

Slime: HM09, and detailing the maps

..and everyone else who helped test various times when I hosted :)


## Notes

The KnownLetters global array stores all letters known to the client. A value of -1 in it means that the letter is unknown, and a value of -2 signifies the end of the word. A value of -11 means "make unknown if no value there", and -12 means "make end if no value there". When adjusted to be the proper charcter value, they become -2, -3, -12, and -13.
This is for clients, so that even spectators can see the current word in play.

The chr argument for HANGMAN\_REVEALLETTER needs to be one lower than the character itself. This is because elements in a global array are 0 by default, and we don't want to eliminate the null byte as a valid character. Not that it'll ever be used, but it's nice to know it's there.
