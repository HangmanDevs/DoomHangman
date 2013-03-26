#include "zcommon.acs"

#include "commonFuncs.h"
#include "stralloc.h"

#include "hangdefs.h"
#include "hangwords.h"
#include "hangfuncs.h"

#include "wordchoose.h"
#include "pick.h"
#include "hangmanhud.h"

int winStrs[5] =
{
    "",
    "",
    "",
    "",
    "Go kill each other.",
};


int ejectStrs[5] =
{
    "\chBLUE TEAM\c- has been ejected",
    "\cgRED TEAM\c- has been ejected",
    "\cdGREEN TEAM\c- has been ejected",
    "\cfGOLD TEAM\c- has been ejected",
    "\cgEVERYONE\c- has been ejected"
};

int ejected[5]= {0};

int spawnItem[12] =
{
    "SuperShotgun", "Minigun", "RocketLauncher",
    "GrenadeLauncher", "Railgun", "CellPack", "RocketBox",
    "ShellBox", "ClipBox", "StrengthRune", "RageRune", "SpreadRune"
};

int acsToExecute[5];

int tColors[4][3]  = { {64,  64,  255}, {255, 0,   0},   {0,   255, 0},   {255, 224, 0} };
int tColors2[4][3] = { {160, 160, 255}, {255, 128, 128}, {128, 255, 128}, {255, 240, 128} };


function int sectorTeam(int team)
{
    switch (team)
    {
        case 0:
            return 0;
            break;

        case 1:
            return 1;
            break;

        case 2:
            return 3;
            break;

        case 3:
            return 4;
            break;
    }

    return -1;
}


script 494 (int whichTeam)
{
    int adjusted;
    int i;

    SetFont("BIGFONT");
    HudMessageBold(s:ejectStrs[whichTeam]; HUDMSG_FADEOUT, 21, CR_WHITE, 1.5, 0.7, 5.0);

    if (whichTeam == 4)
    {
        for (i = 0; i < 5; i++)
        {
            if (ejected[i] == 1)
            {
                continue;
            }

            if (i != 2)
            {
                Ceiling_RaiseByValue(5080+i, 32, 96);
                FloorAndCeiling_LowerRaise(5180+i, 32, 8);
            }

            ejected[i] = 1;
        }

        Delay(18);
        for (i = 0; i < 5; i++)
        {

            if (i != 2)
            {
                Sector_SetGravity(5080+i, 0, 0);
                Sector_SetGravity(5180+i, 0, 0);
                Sector_SetGravity(5280+i, 0, 0);
                ACS_ExecuteAlways(122, 0, 5080+i, 1, 0);
                ACS_ExecuteAlways(122, 0, 5180+i, 1, 0);
                ACS_ExecuteAlways(122, 0, 5280+i, 1, 0);
            }

            ACS_ExecuteAlways(383, 0, i, 184, 0);
        }
    }
    else
    {
        adjusted = sectorTeam(whichTeam);

        if (ejected[whichTeam] == 0)
        {
            Ceiling_MoveToValue(5080+adjusted, 32, 96);
            FloorAndCeiling_LowerRaise(5180+adjusted, 32, 8);
        }

        ejected[whichTeam] = 1;

        Delay(18);

        Sector_SetGravity(5080+adjusted, 0, 0);
        Sector_SetGravity(5180+adjusted, 0, 0);
        Sector_SetGravity(5280+adjusted, 0, 0);
        ACS_ExecuteAlways(122, 0, 5080+adjusted, 1, 0);
        ACS_ExecuteAlways(122, 0, 5180+adjusted, 1, 0);
        ACS_ExecuteAlways(122, 0, 5280+adjusted, 1, 0);

        ACS_ExecuteAlways(383, 0, whichTeam, 184, 0);
    }
}

script 493 (int whichTeam)
{
    int adjusted;
    int i; int j;

    SetFont("BIGFONT");
    HudMessageBold(s:winStrs[whichTeam]; HUDMSG_FADEOUT, 22, CR_WHITE, 1.5, 0.6, 5.0);

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (i != 2)
            {
                Ceiling_LowerAndCrush(5080+i, 32, 100);
                Floor_MoveToValue(5180+i, 32, 16);
                Ceiling_MoveToValue(5180+i, 32, 80);
            }
        }
        Delay(5);
    }

    Delay(105);

    Generic_Door(1337, 32, 1, 0, 0);

    for (i = 0; i < 5; i++)
    {
        ejected[i] = 0;

        if (i != 2)
        {

            Sector_SetGravity(5080+i, 1, 0);
            Sector_SetGravity(5180+i, 1, 0);
            Sector_SetGravity(5280+i, 1, 0);
            ACS_ExecuteAlways(122, 0, 5080+i, 0, 0);
            ACS_ExecuteAlways(122, 0, 5180+i, 0, 0);
            ACS_ExecuteAlways(122, 0, 5280+i, 0, 0);
            Ceiling_MoveToValue(5080+i, 2, 0);
        }

        if ( (i == whichTeam) && (whichTeam != 4) )
        {
            ACS_ExecuteAlways(383, 0, i, 185, 0);
        }
        else
        {
            ACS_ExecuteAlways(383, 0, i, 186, 0);
        }

        if ( (i == whichTeam) || (whichTeam == 4) )
        {
            Door_Open(6080+sectorTeam(i), 64);
        }
    }
}

script 491 (void) {}
script 492 (void) {}


script 13 (int whichTeam)
{
    int adjusted = sectorTeam(whichTeam);

    if (LineSide() == LINE_BACK)
    {
        Door_Close(6080 + adjusted, 64);
        Delay(18);

        if (whichTeam == PlayerTeam())
        {
            Door_Open(6180 + adjusted, 64);
            Delay(35);
            Door_Close(6180 + adjusted, 64);
            Delay(18);
            Door_Open(6080 + adjusted, 64);
        }
        else
        {
            Delay(17);
            FadeTo(255, 0, 0, 0.8, 0.5);
            Delay(18);
            GiveInventory("NoGodMode", 1);
            DamageThing(0);
            Delay(17);
            Door_Open(6080 + adjusted, 64);
            FadeTo(255, 0, 0, 0.0, 0.5);
        }
    }
}


script 51 OPEN
{
    int i; int j;

    ACS_ExecuteAlways(122, 0, 2, 1, 0);
    Sector_SetGravity(2, 0, 0);
    ACS_ExecuteAlways(122, 0, 22, 1, 0);
    Sector_SetGravity(22, 0, 0);

    for (i = 0; i < 5; i++)
    {
        j = sectorTeam(i);

        Sector_SetColor(5580 + j, tColors[i][0], tColors[i][1], tColors[i][2], 0);
        Sector_SetColor(5580 + j, tColors[i][0], tColors[i][1], tColors[i][2], 0);

        Sector_SetGravity(5080+j, 1, 0);
        Sector_SetGravity(5180+j, 1, 0);
        Sector_SetGravity(5280+j, 1, 0);
        ACS_ExecuteAlways(122, 0, 5080+j, 0, 0);
        ACS_ExecuteAlways(122, 0, 5180+j, 0, 0);
        ACS_ExecuteAlways(122, 0, 5280+j, 0, 0);
    }

    for (i = 0; i < 5; i++)
    {
        j = sectorTeam(i);

        Sector_SetColor(5680 + j, tColors2[i][0], tColors2[i][1], tColors2[i][2], 0);
        Sector_SetColor(5680 + j, tColors2[i][0], tColors2[i][1], tColors2[i][2], 0);
    }
}

script 52 ENTER
{
    int i; int j;

    for (i = 1; i < 13; i++)
    {
        for (j = 0; j < 4; j++)
        {
            SpawnSpot(spawnItem[i-1], 4000+i, 0, 0);
        }
    }
}


script 53 ENTER
{
    int myTeam;
    int lastScript;

    int pln = PlayerNumber();


    ClearInventory();
    GiveInventory("Fist", 1);
    GiveInventory("NoPull", 1);
    GiveInventory("YesGodMode", 1);
    SetActorProperty(0, APROP_Health, 100);

    while (PlayerInGame(pln) )
    {
        myTeam = PlayerTeam();

        if (acsToExecute[myTeam] != lastScript)
        {
            if (acsToExecute[myTeam] % 1000 != 0)
            {
                ACS_ExecuteAlways(acsToExecute[myTeam] % 1000, 0, myTeam, 0, 0);
            }
            lastScript = acsToExecute[myTeam];
        }
        Delay(1);
    }
}

script 54 RESPAWN
{
    ClearInventory();
    GiveInventory("Fist", 1);
    GiveInventory("NoPull", 1);
}


script 383 (int whichTeam, int whichScript)
{
    acsToExecute[whichTeam] = whichScript;
    Delay(1);
    acsToExecute[whichTeam] = 0;
}


script 184 (int yourTeam)
{
    LocalSetMusic("D_RINGIN");

    GiveInventory("YesPull", 1);
    GiveInventory("NoGodMode", 1);

    Delay(35);

    GiveInventory("NoPull", 1);

    int i, j;

    for (i = 1; i < 400; i++)
    {
        j = i-7;

        if (j > 0) { DamageThing(j, MOD_ICE); }

        if (GetActorProperty(0, APROP_Health) < 1)
        {
            LocalSetMusic("D_SILENT");
            break;
        }

        if (!ejected[yourTeam] && !CheckActorCeilingTexture(0, "F_SKY1"))
        {
            LocalSetMusic("*");
            break;
        }

        Delay(35);
    }
}

script 185 (int yourTeam)
{
    GiveInventory("NoPull", 1);
    GiveInventory("YesGodMode", 1);
}

script 186 (int yourTeam)
{
    GiveInventory("NoPull", 1);
    GiveInventory("NoGodMode", 1);
}


script 122 (int whichSector, int flag)
{
    ACS_ExecuteAlways(123, 0, whichSector, flag);
    Sector_ChangeFlags(whichSector, SECF_SILENT * (flag != 0), SECF_SILENT * (flag == 0) );
}


script 123 (int whichSector, int flag) clientside
{
    Sector_ChangeFlags(whichSector, SECF_SILENT * (flag != 0), SECF_SILENT * (flag == 0) );
}
