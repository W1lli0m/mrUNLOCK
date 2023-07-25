/*
# (c) B.Kerler 2019-2023 under GPLv3 license
# If you use my code, make sure you refer to my name
#
# !!!!! If you use this code in commercial products, your product is automatically
# GPLv3 and has to be open sourced under GPLv3 as well. !!!!!
# https://github.com/bkerler/edl
# This is a derived code from sierrakeygen.py done by B.Kerler, remained same license term as GPLv3
*/
#ifndef NULL_CHAR
#define NULL_CHAR   0x00
#endif
#ifndef _SIERRAKEYGEN_
#define _SIERRAKEYGEN_
#define SIERRA_KEY_NULL             0x00000000
#define MDM8200_KY                  0x00000001
#define MDM9200_KY                  0x00000002
#define MDM9200_V1_KY               0x00000004
#define MDM9200_V2_KY               0x00000008
#define MDM9200_V3_KY               0x00000010
#define MDM9x15_KY                  0x00000020
#define MDM9x07_KY                  0x00000040
#define MDM9x30_KY                  0x00000080
#define MDM9x30_V1_KY               0x00000100
#define MDM9x40_KY                  0x00000200
#define MDM9x50_KY                  0x00000400
#define MDM9x06_KY                  0x00000800
#define SDX55_KY                    0x00001000
#define SDX65_KY                    0x00002000
#define MDM9x15A_KY                 0x00004000
#define SDX62_KY                    0x00008000
#define SDX65_NG_KY                 0x40002000
#define SIERRAKEYGEN_NG             0x40000000
#define SIERRA_KEY_NOTFOUND         0x80000000

struct sierraKeyModelSTRUCT {
    unsigned long keyModel;
    char    keyName[64];
};


#define SIERRAKEY_MODEL_NUMBERS 17  
sierraKeyModelSTRUCT sierraKeyModelTBL[] = { {SIERRA_KEY_NULL,   "UNKNOWN"},
                                                {MDM8200_KY,        "MDM8200"},
                                                {MDM9200_KY,        "MDM9200"},
                                                {MDM9200_V1_KY,     "MDM9200_V1"},
                                                {MDM9200_V2_KY,     "MDM9200_V2"},
                                                {MDM9200_V3_KY,     "MDM9200_V3"},
                                                {MDM9x15_KY,        "MDM9x15"},
                                                {MDM9x07_KY,        "MDM9x07"},
                                                {MDM9x30_KY,        "MDM9x30"},
                                                {MDM9x30_V1_KY,     "MDM9x30_V1"},
                                                {MDM9x40_KY,        "MDM9x40"},
                                                {MDM9x50_KY,        "MDM9x50"},
                                                {MDM9x06_KY,        "MDM9x06"},
                                                {SDX55_KY,          "SDX55"},
                                                {SDX65_KY,          "SDX65"},
                                                {MDM9x15A_KY,       "MDM9x15A"},
                                                {SDX62_KY,          "SDX62"},
                                                {SDX65_NG_KY,       "SDX65_NG"},
                                                {SIERRA_KEY_NOTFOUND,""}
};


#define SIERRA_KEYTYPE_OPENLOCK         0
#define SIERRA_KEYTYPE_OPENMEP          1
#define SIERRA_KEYTYPE_OPENCND          2

struct sierraProdTable {
    unsigned int	chipGeneration;
    int challengelen;
    int sierraInit_tbl[5];
    int sierraAlgo_tbl[8];
    unsigned char   challenge[16];
    unsigned char* keySeed;
    int keyType;
    unsigned char openlockSeed[16];
    unsigned char openmepSeed[16];
    unsigned char opencndSeed[16];
    unsigned char sierraKeys[256];
};

sierraProdTable sierraProd[] = {
    {MDM8200_KY,                                    
                            8,                      
                            {1,3,5,7,0},            
                            {2,4,1,3,0,3,4,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},   
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},  
                            {0x00}},                
    {MDM9200_KY,                                   
                            8,                     
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},   
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x00}},               
    {MDM9200_V1_KY,                                 
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x39, 0xC6, 0x7B, 0x04, 0xCA, 0x50, 0x82, 0x1F, 0x19, 0x63, 0x36, 0xDE, 0x81, 0x49, 0xF0, 0xD7},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},   
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x00}},                
    {MDM9200_V2_KY,                                 
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xDE, 0xA5, 0xAD, 0x2E, 0xBE, 0xE1, 0xC9, 0xEF, 0xCA, 0xF9, 0xFE, 0x1F, 0x17, 0xFE, 0xED, 0x3B},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},  
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x00}},                
    {MDM9200_V3_KY,                                 
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x8F, 0xA5, 0x85, 0x05, 0x5E, 0xCF, 0x44, 0xA0, 0x98, 0x8B, 0x09, 0xE8, 0xBB, 0xC6, 0xF7, 0x65},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},   
                            {0x8F, 0xA5, 0x85, 0x05, 0x5E, 0xCF, 0x44, 0xA0, 0x98, 0x8B, 0x09, 0xE8, 0xBB, 0xC6, 0xF7, 0x65},   
                            {0x00}},                
    {MDM9x15_KY,                                    
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,   
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x61, 0x94, 0xCE, 0xA7, 0xB0, 0xEA, 0x4F, 0x0A, 0x73, 0xC5, 0xC3, 0xA6, 0x5E, 0xEC, 0x1C, 0xE2},   
                            {0xF0, 0x14, 0x55, 0x0D, 0x5E, 0xDA, 0x92, 0xB3, 0xA7, 0x6C, 0xCE, 0x84, 0x90, 0xBC, 0x7F, 0xED},   
                            {0x00}},                
    {MDM9x07_KY,                                   
                            8,                     
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x4D, 0x42, 0xD8, 0xC1, 0x25, 0x44, 0xD8, 0xA0, 0x1D, 0x80, 0xC4, 0x52, 0x8E, 0xEC, 0x8B, 0xE3},  
                            {0xED, 0xA9, 0xB7, 0x0A, 0xDB, 0x85, 0x3D, 0xC0, 0x92, 0x49, 0x7D, 0x41, 0x9A, 0x91, 0x09, 0xEE},   
                            {0x4D, 0x42, 0xD8, 0xC1, 0x25, 0x44, 0xD8, 0xA0, 0x1D, 0x80, 0xC4, 0x52, 0x8E, 0xEC, 0x8B, 0xE3},   
                            {0x00}},                
    {MDM9x30_KY,                                    
                            8,                     
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x3B, 0x18, 0x99, 0x6B, 0x57, 0x24, 0x0A, 0xD8, 0x94, 0x6F, 0x8E, 0xD9, 0x90, 0xBC, 0x67, 0x56},   
                            {0xFE, 0xD4, 0x40, 0x52, 0x2D, 0x4B, 0x12, 0x5C, 0xE7, 0x0D, 0xF8, 0x79, 0xF8, 0xC0, 0xDD, 0x37},   
                            {0x3B, 0x18, 0x99, 0x6B, 0x57, 0x24, 0x0A, 0xD8, 0x94, 0x6F, 0x8E, 0xD9, 0x90, 0xBC, 0x67, 0x56},   
                            {0x00}},                
    {MDM9x30_V1_KY,                                 
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xC5, 0x50, 0x40, 0xDA, 0x23, 0xE8, 0xF4, 0x4C, 0x29, 0xE9, 0x07, 0xDE, 0x24, 0xE5, 0x2C, 0x1D},   
                            {0x98, 0xE1, 0xC1, 0x93, 0xC3, 0xBF, 0xC3, 0x50, 0x8D, 0xA1, 0x35, 0xFE, 0x50, 0x47, 0xB3, 0xC4},   
                            {0xC5, 0x50, 0x40, 0xDA, 0x23, 0xE8, 0xF4, 0x4C, 0x29, 0xE9, 0x07, 0xDE, 0x24, 0xE5, 0x2C, 0x1D},   
                            {0x00}},                
    {MDM9x40_KY,                                    
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x8A, 0x56, 0x03, 0xF0, 0xBB, 0x9C, 0x13, 0xD2, 0x4E, 0xB2, 0x45, 0xAD, 0xC4, 0x0A, 0xE7, 0x52},   
                            {0x2A, 0xEF, 0x07, 0x2B, 0x19, 0x60, 0xC9, 0x01, 0x8B, 0x87, 0xF2, 0x6E, 0xC1, 0x42, 0xA8, 0x3A},   
                            {0x8A, 0x56, 0x03, 0xF0, 0xBB, 0x9C, 0x13, 0xD2, 0x4E, 0xB2, 0x45, 0xAD, 0xC4, 0x0A, 0xE7, 0x52},   
                            {0x00}},                
    {MDM9x50_KY,                                    
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x4F, 0x4D, 0x41, 0x52, 0x20, 0x44, 0x49, 0x44, 0x20, 0x54, 0x48, 0x49, 0x53, 0x2E, 0x2E, 0x2E},   
                            {0x47, 0x4F, 0x4F, 0x44, 0x4A, 0x4F, 0x42, 0x44, 0x45, 0x43, 0x4F, 0x44, 0x49, 0x4E, 0x47, 0x2E},   
                            {0x4F, 0x4D, 0x41, 0x52, 0x20, 0x44, 0x49, 0x44, 0x20, 0x54, 0x48, 0x49, 0x53, 0x2E, 0x2E, 0x2E},   
                            {0x00}},                
    {MDM9x06_KY,                                    
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0x12, 0xF0, 0x79, 0x6B, 0x19, 0xC7, 0xF4, 0xEC, 0x50, 0xF3, 0x8C, 0x40, 0x02, 0xC9, 0x43, 0xC8},   
                            {0x78, 0x19, 0xC5, 0x6D, 0xC3, 0xD8, 0x25, 0x3E, 0x51, 0x60, 0x8C, 0xA7, 0x32, 0x83, 0x37, 0x9D},   
                            {0x12, 0xF0, 0x79, 0x6B, 0x19, 0xC7, 0xF4, 0xEC, 0x50, 0xF3, 0x8C, 0x40, 0x02, 0xC9, 0x43, 0xC8},   
                            {0x00}},                
    {SDX55_KY,                
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},   
                            {0x49, 0x42, 0xFF, 0x76, 0x8A, 0x95, 0xCF, 0x7B, 0xA3, 0x47, 0x5F, 0xF5, 0x8F, 0xD8, 0x45, 0xE4},   
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},   
                            {0x00}},                
    {SDX65_KY,                
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},   
                            {0x49, 0x42, 0xFF, 0x76, 0x8A, 0x95, 0xCF, 0x7B, 0xA3, 0x47, 0x5F, 0xF5, 0x8F, 0xD8, 0x45, 0xE4},   
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},   
                            {0x00} },               
    {SDX62_KY,                
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},  
                            {0x49, 0x42, 0xFF, 0x76, 0x8A, 0x95, 0xCF, 0x7B, 0xA3, 0x47, 0x5F, 0xF5, 0x8F, 0xD8, 0x45, 0xE4},   
                            {0xF8, 0x1A, 0x3A, 0xCC, 0xAA, 0x2B, 0xA5, 0xE8, 0x8B, 0x53, 0x5A, 0x55, 0xB9, 0x65, 0x57, 0x98},   
                            {0x00} },               
    {MDM9x15A_KY,                                  
                            8,                     
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                
                            {0x00},                
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xC7, 0xE6, 0x39, 0xFE, 0x0A, 0xC7, 0xCA, 0x4D, 0x49, 0x8F, 0xD8, 0x55, 0xEB, 0x1A, 0xCD, 0x8A},  
                            {0x54, 0xC9, 0xC7, 0xA4, 0x02, 0x1C, 0xB0, 0x11, 0x05, 0x22, 0x39, 0xB7, 0x84, 0xEF, 0x16, 0xCA},  
                            {0xC7, 0xE6, 0x39, 0xFE, 0x0A, 0xC7, 0xCA, 0x4D, 0x49, 0x8F, 0xD8, 0x55, 0xEB, 0x1A, 0xCD, 0x8A},  
                            {0x00}},                
    {SDX65_NG_KY,                                   
                            8,                      
                            {7,3,0,1,5},            
                            {4,2,1,0,3,2,0,0},      
                            {0x00},                 
                            {0x00},                 
                            SIERRA_KEYTYPE_OPENLOCK,    
                            {0xF2, 0x4A, 0x9A, 0x2C, 0xDA, 0x3D, 0xA5, 0xE2, 0x6B, 0x56, 0x9A, 0x45, 0x29, 0x25, 0x77, 0x9A},   
                            {0x49, 0x42, 0xFF, 0x76, 0x8A, 0x95, 0xCF, 0x7B, 0xA3, 0x47, 0x5F, 0xF5, 0x8F, 0xD8, 0x45, 0xE4},  
                            {0x46, 0x30, 0x33, 0x43, 0x44, 0x36, 0x42, 0x34, 0x41, 0x32, 0x31, 0x32, 0x30, 0x35, 0x39, 0x37},  
                            {0x00} },                
    {SIERRA_KEY_NOTFOUND}
};


unsigned long   sierraKeyModel = SIERRA_KEY_NULL;
unsigned char rtbl[20] = { 0x00 };
unsigned char tbl[256] = { 0x00 };
void SierraAlgo(sierraProdTable* scb, unsigned char* rBuffer, unsigned char* challenge);
void SierraPreInit(int icounter, unsigned char* keySeed, int keylen, int* cl, int* mcount, int* counter);
void SierraInit(sierraProdTable* scb, int keylen);
void SierraKeygen(sierraProdTable* scb, unsigned char* challenge, int challengelen, int keylen);
void SierraGenerator(sierraProdTable* scb, unsigned char* iChallenge);
extern void bytes2HexString(unsigned char* bBUF);
extern void hexString2Bytes(unsigned char* bBUF, int length);

void SierraAlgo(sierraProdTable* scb, unsigned char* rBuffer, unsigned char* challenge)
{
    int a = scb->sierraAlgo_tbl[0],
        b = scb->sierraAlgo_tbl[1],
        c = scb->sierraAlgo_tbl[2],
        d = scb->sierraAlgo_tbl[3],
        e = scb->sierraAlgo_tbl[4],
        ret = scb->sierraAlgo_tbl[5],
        ret2 = scb->sierraAlgo_tbl[6],
        flag = scb->sierraAlgo_tbl[7];
    unsigned char v0, v1, v2, v4, v5, v6, u, v;

    v6 = rtbl[e];
    v0 = (v6 + 1) & 0xFF;
    rtbl[e] = v0;
    rtbl[c] = (tbl[v6 + flag & 0xFF] + rtbl[c]) & 0xFF;
    v4 = rtbl[c] & 0xFF;
    v2 = rtbl[b] & 0xFF;
    v1 = tbl[(v2 & 0xFF)];
    tbl[(v2 & 0xFF)] = tbl[(v4 & 0xFF)];
    v5 = rtbl[d] & 0xFF;
    tbl[(v4 & 0xFF)] = tbl[(v5 & 0xFF)];
    tbl[(v5 & 0xFF)] = tbl[(v0 & 0xFF)];
    tbl[v0] = v1 & 0xFF;
    u = tbl[(tbl[(tbl[((rtbl[a] + tbl[(v1 & 0xFF)]) & 0xFF)] + tbl[(v5 & 0xFF)] + tbl[(v2 & 0xFF)] & 0xFF)] & 0xFF)];
    v = tbl[((tbl[(v4 & 0xFF)] + v1) & 0xFF)];
    rtbl[ret] = u ^ v ^ *(challenge);
    rtbl[a] = (tbl[(v1 & 0xFF)] + rtbl[a]) & 0xFF;
    rtbl[ret2] = *(challenge) & 0xFF;
    *(rBuffer) = rtbl[ret] & 0xFF;
}

void SierraPreInit(int icounter, unsigned char* keySeed, int keylen, int* cl, int* mcount, int* counter)
{
    int tmp, tmp2, tmp3;
    int i;

    if (icounter != 0) {
        tmp2 = 0;
        i = 1;
        while (i < icounter)
            i = i * 2 + 1;

        while (TRUE) {
            tmp = *(mcount);
            *(mcount) = tmp + 1;
            *(cl) = (keySeed[tmp & 0xFF] + tbl[*(cl) & 0xFF]) & 0xFF;
            if (*(mcount) >= keylen) {
                *(mcount) = 0;
                *(cl) = ((*(cl) & 0xFF) + keylen) & 0xFF;
            }
            tmp2++;
            tmp3 = ((*(cl) & 0xFF) & i) & 0xFF;
            if (tmp2 >= 0x0B)
                tmp3 = icounter % tmp3;
            if (tmp3 <= icounter)
                break;
        }
        icounter = tmp3 & 0xFF;
    }
    *(counter) = icounter;
}

void SierraInit(sierraProdTable* scb, int keylen)
{
    int mcount = 0;
    int cl = 0;
    int i;
    int counter;
    unsigned char m;

    for (i = 0; i < 256; i++)
        tbl[i] = (unsigned char)i;

    i = 0xFF;
    counter = i;
    while (i >= 0) {
        SierraPreInit(i, scb->keySeed, keylen, &cl, &mcount, &counter);
        m = tbl[i];
        tbl[i] = tbl[counter & 0xFF];
        i--;
        tbl[counter & 0xFF] = m;
    }
    rtbl[0] = (scb->sierraInit_tbl[0] == 0) ? tbl[cl & 0xFF] : tbl[scb->sierraInit_tbl[0]];
    rtbl[1] = (scb->sierraInit_tbl[1] == 0) ? tbl[cl & 0xFF] : tbl[scb->sierraInit_tbl[1]];
    rtbl[2] = (scb->sierraInit_tbl[2] == 0) ? tbl[cl & 0xFF] : tbl[scb->sierraInit_tbl[2]];
    rtbl[3] = (scb->sierraInit_tbl[3] == 0) ? tbl[cl & 0xFF] : tbl[scb->sierraInit_tbl[3]];
    rtbl[4] = (scb->sierraInit_tbl[4] == 0) ? tbl[cl & 0xFF] : tbl[scb->sierraInit_tbl[4]];
}

void SierraKeygen(sierraProdTable* scb, unsigned char* challenge, int challengelen, int keylen)
{
    int i;

    SierraInit(scb, keylen);

    for (i = 0; i < challengelen; i++)
        SierraAlgo(scb, &scb->sierraKeys[i], challenge + i);

    scb->sierraKeys[challengelen] = NULL_CHAR;

}
void SierraGenerator(sierraProdTable* scb, unsigned char* iChallenge)
{
    unsigned char oChallenge[16] = { NULL_CHAR };
    int clen = scb->challengelen;

    switch (scb->keyType) {
    case SIERRA_KEYTYPE_OPENMEP:    
        scb->keySeed = scb->openmepSeed;
        break;
    case SIERRA_KEYTYPE_OPENCND:    
        scb->keySeed = scb->opencndSeed;
        break;
    case SIERRA_KEYTYPE_OPENLOCK:   
    default:
        scb->keySeed = scb->openlockSeed;
        break;
    }
    
    for (int i = 0; i < 16; i++)
        oChallenge[i] = *(iChallenge + i);
    
    hexString2Bytes(oChallenge, 16);
    SierraKeygen(scb, oChallenge, clen, 16);
    bytes2HexString(scb->sierraKeys);
}
#endif
