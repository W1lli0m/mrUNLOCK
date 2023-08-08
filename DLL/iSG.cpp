#define WIN32_LEAN_AND_MEAN

#include "pch.h" 
#include <utility>
#include <limits.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string.h>
#include "sierrakeygen.h"
#include "iSG.h"


sierraKeyModelSTRUCT* sTBL = sierraKeyModelTBL;
sierraProdTable* sKGP = sierraProd;
unsigned char vTable[16] = { 0x00 };
const char    ascii0toF[] = "0123456789ABCDEF";

void bytes2HexString(unsigned char* bValue);
void hexString2Bytes(unsigned char* strChallenge, int length);
char UpperCase(char t);
BOOL IsAlpha(char cP);
BOOL IsDigits(char cP);
BOOL IsAlphaHex(char cP);
void upDateSGMInfo(int sgm);

char UpperCase(char t)
{
    if ((t >= 'a') && (t <= 'z'))
        return (t & 0xDF);
    else
        return (t);
}
BOOL IsAlpha(char cP)
{
    return ((UpperCase(cP) >= 'A') && (UpperCase(cP) <= 'Z'));
}

BOOL IsDigits(char cP)
{
    return ((cP >= '0') && (cP <= '9'));
}

BOOL IsAlphaHex(char cP)
{
    return ((UpperCase(cP) >= 'A') && (UpperCase(cP) <= 'F'));
}

void bytes2HexString(unsigned char* bValue)
{
    for (int i = 0; i < 8; i++)
        vTable[i] = *(bValue + i);

    for (int i = 0; i < 8; i++) {
        *(bValue + (i * 2)) = ascii0toF[(vTable[i] >> 4) & 0x0F];
        *(bValue + (i * 2) + 1) = ascii0toF[vTable[i] & 0x0F];
    }
}

void hexString2Bytes(unsigned char* strChallenge, int length)
{
    for (int i = 0; i < length; i++)
        vTable[i] = IsAlphaHex(*(strChallenge + i)) ? UpperCase(*(strChallenge + i)) : *(strChallenge + i);
    for (int i = 0; i < (length / 2); i++) {
        *(strChallenge + i) = IsAlphaHex(vTable[i * 2]) ? ((vTable[i * 2] - 'A' + 10) * 16) : ((vTable[i * 2] - '0') * 16);
        *(strChallenge + i) += IsAlphaHex(vTable[i * 2 + 1]) ? (vTable[i * 2 + 1] - 'A' + 10) : (vTable[i * 2 + 1] - '0');
    }
    for (int i = (length / 2); i < length; i++)
        *(strChallenge + i) = 0x00;
}

void upDateSGMInfo(int sgm)
{
    while (TRUE) {
        if (sKGP->chipGeneration == SIERRA_KEY_NOTFOUND) {
            sKGP = (sierraProdTable*)NULL;
            break;
        }
        else {
            if (sKGP->chipGeneration == (sTBL + sgm)->keyModel)
                break;
            else
                sKGP++;
        }
    }
}

void iSG(char *strChallenge, char *strPassphrase,int keyModel,int keyType)
{
    char *sP = NULL;
    char* tP=NULL;
    upDateSGMInfo(keyModel);
    sKGP->keyType = keyType;
    SierraGenerator(sKGP, (unsigned char *)strChallenge);
    sP = (char *)sKGP->sierraKeys;
    tP = strPassphrase;
    while (*sP != NULL_CHAR)
        *tP++ = *sP++;
    *tP = NULL_CHAR;
}

WORD iSG_Version()
{
    return (0x0100);
}
