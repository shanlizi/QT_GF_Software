#ifndef BIN_H
#define BIN_H
#include "typedefine.h"
#include <qglobal.h>
#pragma pack(1)

#define PI           (3.1415926535898)
#define P31          (2147483647.0)  //2^31-1
#define P15          (32767.0)  //2^15-1
#define MAX_LENTH     512


enum ENUM_UART_STREAM_TYPE
{
    GNSS = 10,
    T_ID,
    T_LEN,
    T31,
    T32,
    T33,
    T34,
    T35,
    T36
};




typedef struct _t7373H
{
    u2 u2DataFlag;
    u2 u2SVNum;
    u2 u2Serial;
    u2 u2SVNo;
    u2 u2FreNo;
    u2 u2DiffFlag;
    u2 u2PRFlag;
    u2 u2ClockCorrectFlag;
    i4 i4ClockCorrect;
    i1 i1Rest[20];
}T7373H;

typedef struct _t31H
{
    i1 i1model;
}T31H;

typedef struct _t32H
{
    u2 u2ID;
    i1 i1flag;
}T32H;

typedef struct _t36H
{
    i1 i1Type[50];
    i1 i1version[50];
}T36H;

typedef struct _tChannel
{
    i2 i2OriginV;
    i2 i2HighV;
    i2 i2Slope;
    i1 i1Range;
}StrChannel;

typedef struct _tAcqParam
{
    i1 i1Model;
    StrChannel mChannel[16];
}TAcqParam_13H;

typedef struct _tAcqData
{
    u2 u2Time;
    u2 u2OriginData[18];
    u2 u2RealData[16];
}T33H;

typedef struct _tCPM
{
    u1     u1Zero;
    i1     i1Flag_CZ;
}TCPM;


int BIN_ParserFrame(char Buf);
extern T7373H g_T7373;
extern T31H   g_T31;
extern T32H   g_T32;
extern T36H   g_T36;
extern T33H   g_T33;
extern u1 m_BuffRecv[MAX_LENTH];
//extern TGGA Bin_GGA;




#endif // BIN_H
