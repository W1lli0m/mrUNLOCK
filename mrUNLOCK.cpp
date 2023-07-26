/*
* This code is designed to be a command line interpreter to send commands via AT command console
* No any warranty provided by this code, users who take it to program/change the behavior of the device, is awared of consequence and liability
* Author has no intention to encourage any illegal actions.
* It is provided to prove of concept for creating a simple command vehicle.
*/
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma warning(disable:6011) 


#include <windows.h>
#include <winsock2.h>
#include <windowsx.h>
#include <ws2tcpip.h>
#include <libloaderapi.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "sierrakeygen.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define NULL_CHAR   0x00
#define CR          0x0d
#define LF          0x0a
#define SPACE       0x20

char    devIPAddress[64] = { '1','9','2','.','1','6','8','.','1','.','1',0x00 };
char    atPort[64] = { '5','5','1','0',0x00 };
char    telnetPort[64] = { '2','3',0x00 };
SOCKET          tSocket, cSocket;
struct addrinfo* result = NULL,* ptr = NULL, hints;
BOOL    ipAVAIL = FALSE;
BOOL    portAVAIL = FALSE;
BOOL    sgAVAIL = FALSE;
BOOL    socketAVAIL = FALSE;
BOOL    bScriptSectionFound = FALSE;
WSADATA wsaData;
int iResult;
int tOffset;
int SGModel = 0;
char    socketBuffer[1024];
_Post_ _Notnull_ FILE* pFile = NULL;
char    pBuffer[1024] = { 0x00 };
char    keyChallenge[64] = { 0x00 };
char    keyPassphrase[64] = { 0x00 };
unsigned char vTable[16] = { 0x00 };
const char    ascii0toF[] = "0123456789ABCDEF";
char    runScript[64] = { 0x00 };
sierraKeyModelSTRUCT* sTBL = sierraKeyModelTBL;
sierraProdTable* sKGP = sierraProd;


int _a_stricmp(char* str1, char* str2);
char UpperCase(char t);
char* RetrieveSCRDATAString(char* sBuffer);
void bytes2HexString(unsigned char* bBUF);
void hexString2Bytes(unsigned char* bBUF, int length);
BOOL IsDigits(char cP);
BOOL IsAlphaHex(char cP);
BOOL IsAlpha(char cP);
void upDateSGMInfo(int sgm);

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
char UpperCase(char t)
{
    if ((t >= 'a') && (t <= 'z'))
        return (t & 0xDF);
    else
        return (t);
}

BOOL _a_searchString(char* sP, const char* patternP, BOOL bIGNORE_CASE)
{
    int	patternLength;
    char* iP = sP;
    BOOL matched;

    char cC, dD;
    int sLength;
    char* ssP = sP;
    char* ppP = (char*)patternP;
    while (*ssP != NULL_CHAR)
        ssP++;
    while (*ppP != NULL_CHAR)
        ppP++;
    patternLength = (int)(ppP - patternP);
    sLength = (int)((ssP - sP) - patternLength);

    for (int i = 0; i <= sLength; i++) {
        matched = TRUE;
        for (int j = 0; j < patternLength; j++) {
            cC = *(iP + j);
            dD = *(patternP + j);
            if (bIGNORE_CASE) {
                cC = IsAlpha(cC) ? UpperCase(cC) : cC;
                dD = IsAlpha(dD) ? UpperCase(dD) : dD;
            }
            if (cC != dD) {
                matched = FALSE;
                break;
            }
        }
        if (matched)
            return TRUE;
        else
            iP++;
    }
    return FALSE;
}

int _a_stricmp(char* str1, char* str2)
{
    char* s1 = str1, * s2 = str2;
    while (TRUE) {
        if (*s2 == NULL_CHAR)
             return ((int)(s1 - str1));
        else if (UpperCase(*s1) != UpperCase(*s2))
            break;
        else if (*s2 == NULL_CHAR)
            return s1 - str1;
        else if (*s1 == NULL_CHAR)
            break;
        else {
            s1++;
            s2++;
            if (*s1 == NULL_CHAR)
                break;
        }
    }
    return -1;
}

char* RetrieveSCRDATAString(char* sBuffer)
{
    char* sP = sBuffer;
    if (*sP == '\"')
        sP++;
    while (TRUE) {
        if ((*sP == '\"') && (*(sP + 1) != CR) && (*(sP + 1) != LF) && (*(sP+1)!=NULL_CHAR))
            sP++;
        else if (*sP == '\"') {
            *sP = NULL_CHAR;
            return(sBuffer + 1);
        }
        else
            sP++;
        if (*sP==NULL_CHAR)
            return(sBuffer + 1);
    }
}

char *truncateString(char* str)
{
    char *sP = str;
    char* rP = sP;
    while (((*sP == CR) || (*sP == LF)) && (*sP != NULL_CHAR))
        sP++;
    rP = sP;
    while (*sP!=NULL_CHAR) {
        if ((*sP == CR) || (*sP==LF)) {
            *sP = NULL_CHAR;
            return rP;
        }
        else if (*sP == NULL_CHAR)
            return rP;
        else
            sP++;
    }
}

int __cdecl main(int argc, char** argv)
{
    char* tP=NULL,*tPP=NULL;
    int sendLEN = 0;
    int index = 1;
    printf("\nmrUNLOCK v1.10\n\n");

    if (argc > 1) {
        do {
            if (_stricmp("-run", argv[index]) == 0) {
                char* sP = argv[index + 1];
                char* tP = runScript;
                *tP++ = '[';
                while (*sP != NULL_CHAR) {
                    if (*sP == '\"')
                        sP++;
                    else
                        *tP++ = *sP++;
                }
                *tP++ = ']';
                *tP = NULL_CHAR;
            }
            else if (_stricmp("-sgm", argv[index]) == 0) {
                SGModel = atoi(argv[index + 1]);
            }
            else if (_stricmp("-ip", argv[index]) == 0) {
                strcpy(devIPAddress, argv[index + 1]);
                ipAVAIL = TRUE;
            }
            else if (_stricmp("-port", argv[index]) == 0) {
                strcpy(atPort, argv[index + 1]);
                portAVAIL = TRUE;
            }

        } while (++index < argc);
    }
    fopen_s(&pFile, "mrUNLOCK.SCR", "rb");
    if (pFile == NULL) {
        printf("\007\nScript file mrUNLOCK.SCR open error\n");
        exit(-1);
    }
    fseek(pFile, 0L, SEEK_SET);
    if (strlen(runScript) > 0) {
        while (!feof(pFile)) {
            fgets((char*)pBuffer, 1024, pFile);
            if ((tOffset = _a_stricmp(pBuffer, runScript)) != -1) {
                bScriptSectionFound = TRUE;
                break;
            }
        }
        if (!bScriptSectionFound)
            fseek(pFile, 0L, SEEK_SET);
    }
    if (SGModel != 0) {
        upDateSGMInfo(SGModel);
        if (sKGP == NULL)
            printf("SGModel=%d\n", SGModel);
        else {
            printf("SGModel=%s\n", (sTBL + SGModel)->keyName);
            sgAVAIL = TRUE;
        }
    }
    while (!feof(pFile)) {
        fgets((char*)pBuffer, 1024, pFile);
        if (*pBuffer == '#')
            continue;
        if ((!ipAVAIL) && (tOffset = _a_stricmp(pBuffer, (char*)"IP>")) != -1) {
            strcpy(devIPAddress, RetrieveSCRDATAString(pBuffer + tOffset));
            printf("IP=%s\n",devIPAddress);
            ipAVAIL = TRUE;
        }
        else if ((!portAVAIL) && (tOffset = _a_stricmp(pBuffer, (char*)"PORT>")) != -1) {
            strcpy(atPort, RetrieveSCRDATAString(pBuffer + tOffset));
            printf("atPort=%s\n", atPort);
            portAVAIL = TRUE;
        }
        else if ((!sgAVAIL) && (tOffset = _a_stricmp(pBuffer, (char*)"SG_MODEL>")) != -1) {
            SGModel = atoi(RetrieveSCRDATAString(pBuffer + tOffset));
            sgAVAIL = TRUE;
            upDateSGMInfo(SGModel);
            if (sKGP == NULL)
                printf("SGModel=%d\n", SGModel);
            else
                printf("SGModel=%s\n", (sTBL + SGModel)->keyName);
        }
        else if (ipAVAIL && portAVAIL && sgAVAIL) {
            if (!socketAVAIL) {
                printf("\nInitializing WINSOCK.....");
                iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (iResult != 0) {
                    printf("\007\nCan not initialize WINSOCK, error : %d\n", iResult);
                    goto _CLOSE_FILE;
                }
                ZeroMemory(&hints, sizeof(hints));
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;
                iResult = getaddrinfo(devIPAddress, atPort, &hints, &result);
                if (iResult != 0) {
                    printf("\r\007\nWINSOCK getaddrinfo error : %d\n", iResult);
                    goto _CLOSE_WINSOCK;
                }
                for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                    cSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

                    if (cSocket == INVALID_SOCKET) {
                        printf("\r\007\nWINSOCK Socket failed with error: %d\n", WSAGetLastError());
                        goto _CLOSE_WINSOCK;
                    }
                    else {
                        unsigned long l = 1;
                        ioctlsocket(cSocket, FIONREAD, &l);
                    }
                    iResult = connect(cSocket, (SOCKADDR*)ptr->ai_addr, (int)ptr->ai_addrlen);
                    if (iResult == SOCKET_ERROR) {
                        closesocket(cSocket);
                        cSocket = INVALID_SOCKET;
                        continue;
                    }
                    break;
                }
                printf("\r                                                    \r");
                if (cSocket == SOCKET_ERROR) {
                    printf("\n\007Can't connect to the device, program aborting.....\n");
                    goto _CLOSE_SOCKET;
                }
                socketAVAIL = TRUE;
            }

            if ((tOffset = _a_stricmp(pBuffer, (char*)"SEND_CMD>")) != -1) {
                tP = RetrieveSCRDATAString(pBuffer + tOffset);
                printf("SEND_CMD=>%s\n", tP);
                sprintf(socketBuffer, "%s\r", tP);
                sendLEN = strlen(socketBuffer);
                send(cSocket, socketBuffer,sendLEN,0);
                Sleep(100);
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"CMD_ECHO>")) != -1) {
                recv(cSocket, socketBuffer, sendLEN, 0);
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"PUSH_SG_CMD_RESPONSE_STR>")) != -1) {
                tP = RetrieveSCRDATAString(pBuffer + tOffset);
                if (_strnicmp(tP, (char*)"openlock", strlen("openlock")) == 0)
                    sKGP->keyType = SIERRA_KEYTYPE_OPENLOCK;
                else if (_strnicmp(tP, (char*)"openmep", strlen("openmep")) == 0)
                    sKGP->keyType = SIERRA_KEYTYPE_OPENMEP;
                else if (_strnicmp(tP, (char*)"opencnd", strlen("opencnd")) == 0)
                    sKGP->keyType = SIERRA_KEYTYPE_OPENCND;
                else
                    sKGP->keyType = SIERRA_KEYTYPE_OPENLOCK;

                recv(cSocket, socketBuffer, 1024, 0);
                tPP=truncateString(socketBuffer);
                strcpy(keyChallenge, tPP);
                if (_strnicmp(tPP, (char*)"ERROR",5) == 0) {
                    printf("Retrieving challenge ERROR\n");
                    goto _CLOSE_SOCKET;
                }
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"POPUP_SG_SEND_CMD_STR>")) != -1) {
                SierraGenerator(sKGP, (unsigned char*)keyChallenge);
                tP= RetrieveSCRDATAString(pBuffer + tOffset);
                sprintf(socketBuffer, tP, sKGP->sierraKeys);
                strcat(socketBuffer, "\r");
                sendLEN = strlen(socketBuffer);
                send(cSocket, socketBuffer, sendLEN, 0);
                Sleep(100);
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"CMD_SG_STATUS>")) != -1) {
                tP = RetrieveSCRDATAString(pBuffer + tOffset);
                recv(cSocket, socketBuffer, 1024, 0);
                if (_a_searchString(socketBuffer, tP, TRUE))
                    printf("CMD_SG_STATUS matched [%s]\n", tP);
                else if (_a_searchString(socketBuffer, "ERROR", TRUE))
                    printf("CMD_SG_STATUS ERROR\n");
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"DELAY>")) != -1) {
                int delayS= atoi(RetrieveSCRDATAString(pBuffer + tOffset));
                printf("Delaying....");
                Sleep(1000 * delayS);
                printf("\r                         \r");
            }
            else if ((tOffset = _a_stricmp(pBuffer, (char*)"END_CMD>")) != -1) {
                printf("Process completed\n");
                break;
            }
        }
    }
    if (!ipAVAIL)
        printf("\n\007No device IP specified\n");
    if (!portAVAIL)
        printf("\n\007No Port number specified for the device\n");
    if (!sgAVAIL)
        printf("\n\007No sierrakeygen model specified\n");
_CLOSE_SOCKET:
    closesocket(cSocket);
_CLOSE_WINSOCK:
    WSACleanup();
_CLOSE_FILE:
    if (pFile)
        fclose(pFile);
}