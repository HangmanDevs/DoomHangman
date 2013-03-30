#include "zcommon.acs"
//a simple hangman game made very quickly.
//last updated 29/3/2013

/*
script 1 OPEN
{
    while(PlayerCount() < 1) { delay(10); }
    pick();
    delay(70);
    PrintBold(n:victim,s:" \cgHAS BEEN CHOSEN...");
}

script 2 OPEN
{
    while (loop == 1)
    {
        SetFont ("BIGFONT");
        SetHudSize(320, 200, 1);
        HudMessageBold(c:ans[0],c:ans[1],c:ans[2],c:ans[3],c:ans[4],c:ans[5],c:ans[6],c:ans[7],c:ans[8],c:ans[9]; HUDMSG_PLAIN, 1, CR_GREEN, 160.0,100.0, 5.0);
        HudMessageBold(s:"\nPlayers alive: ",d:alive; HUDMSG_PLAIN, 10, CR_GREEN, 160.0,120.0, 5.0);
        delay (10);
    }
}

script 3 (int choice) //holy crap this is so much smaller now
{
    if(count < 10) { Log(n:0,s:" guesses ",c:GetChar(meep,choice-1)); }
    int right = 0;
    SetActivator (-1);
    for(int lol = 0; lol < 10; lol++)
    {
        if(GetChar(meep,choice-1) == letter[lol]) { ans[lol] = letter[lol]; right = 1; }
    }
    if (right == 0 && count < 10)
    {
        SetFont ("BIGFONT");
        HudMessageBold(s:"Wrong!"; HUDMSG_PLAIN, 3, CR_RED, 1.5, 0.8, 1.0);
        Thing_Damage (victim,15*alive,MOD_UNKNOWN); //the more players there are alive, the more screwed you are.
    }
}

//yay, reused code. It works though

script 6 ENTER
{
    Thing_ChangeTID (0,1+PlayerNumber());
    Isdead[PlayerNumber()] = false;
    alive++;
}

script 7 RESPAWN
{
    Thing_ChangeTID (0,1+PlayerNumber());
    Isdead[PlayerNumber()] = false;
    alive++;
}

script 8 DEATH
{
    Thing_ChangeTID (0,0);
    Isdead[PlayerNumber()] = True;
    alive--;
}

script 9 OPEN
{
    While(1)
    {
        for (int num = 1; num < 9; num++)
        {
            If (Isdead[num-1] == true && victim == num)
            {
                PrintBold (n:(num),s:"\c- died! \cgCHOOSING NEW VICTIM...");
                pick();
                delay(70);
                PrintBold(n:victim,s:" \cgHAS BEEN CHOSEN...");
            }
        }
        If (alive == 1)
        {
            loop = 0;
            SetFont ("BIGFONT");
            HudMessageBold(s:"Last man standing!\n\nMap restarting..."; HUDMSG_PLAIN, 4, CR_GOLD, 1.5, 0.8, 5.0);
            delay (105);
            for(int lol = 1; lol < 9; lol++)
            {
                Thing_Damage (lol,999,MOD_UNKNOWN);
            }
            terminate;
        }
    delay(10);
    }
}

script 10 (int gone) DISCONNECT
{
    Thing_ChangeTID (0,0);
    if(Isdead[gone] == false) { alive--; }
    If (Victim == gone+1)
    {
        PrintBold (n:gone+1,s:"\c- has left! \cgCHOOSING NEW VICTIM...");
        pick();
        delay(70);
        PrintBold(n:victim,s:" \cgHAS BEEN CHOSEN...");
    }
}

Script 666 OPEN //scales for snake pillars
{
Sector_setfloorscale(2, 0, 32, 0, 32);
Sector_setceilingscale(2, 0, 32, 0, 32);
}

function void pick(void)
{
    int checkingstuff = 0;
    while(checkingstuff == 0 && PlayerCount() > 0 && alive > 0)
    {
        int picker = Random(1,8);
        If (Isdead[picker-1] == false && PlayerInGame(picker-1) == true)
        {
            victim = picker;
            TeleportOther (picker,10,0);
            checkingstuff++;
        }
    }
}
*/
