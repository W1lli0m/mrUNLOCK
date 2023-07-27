#pragma once

#ifdef __cplusplus  
extern "C" {
#endif  
#ifndef SIERRA_KEYTYPE_OPENLOCK
#define SIERRA_KEYTYPE_OPENLOCK         0
#define SIERRA_KEYTYPE_OPENMEP          1
#define SIERRA_KEYTYPE_OPENCND          2
#endif
	__declspec(dllexport) void iSG(char* strChallenge, char* strPassphrase,int keyModel,int keyType);

#ifdef __cplusplus  
}
#endif  
