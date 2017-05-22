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
    T6969,
    T7A7A,
    T7C7C,
    T7D7D,
    T7E7E,
    T7171,
    T7272,
    T7373,
    T0303,
    T0404,
    T0505,
    T0606,
    T0808,
    T1313,
    T1414,
    T7979
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



int BIN_ParserFrame(char Buf);
extern T7373H g_T7373;
extern u1 m_BuffRecv[MAX_LENTH];
//extern TGGA Bin_GGA;




#endif // BIN_H
