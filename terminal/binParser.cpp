#include "bin.h"
#include "typedefine.h"
#include <QByteArray>
#include "console.h"

enum
{
    S_MATCH_HEAD1 = 0,
    S_MATCH_HEAD2,
    S_MATCH_LEN,
    S_MATCH_ID,
    S_CRC_CHECK,
};

int g_nRevCnt = 0;
u1 m_BuffRecv[MAX_LENTH];
char Flag = GNSS;
T7373H g_T7373 = {0};
T31H   g_T31 = {0};
T32H   g_T32 = {0};
T33H   g_T33 = {0};
T34H   g_T34 = {0};
T35H   g_T35 = {0};
T36H   g_T36 = {0};
static u2 s_u2LenRcv;
i1 i1ID;
u2 u2Len;


u2 u2CheckSum(const u1 *pData, u4 u4Len)
{
    u4 i = 0;
    u2 u2CheckSum = 0;

    for (i=0; i<u4Len; i++)
    {
        u2CheckSum += pData[i];		// ����У������
    }
    return u2CheckSum;
}


int BIN_ParserFrame(char Buf)
{
    m_BuffRecv[g_nRevCnt++] = Buf;
        switch (Flag)
        {
        case GNSS:
            if (g_nRevCnt == 4)
            {
                if ((0x24 == m_BuffRecv[0]) && (0x42 == m_BuffRecv[1]) && (0x49 == m_BuffRecv[2]) && (0x4E == m_BuffRecv[3])) //帧头，$BIN,对应0X24 42 49 4E
                {
                    Flag = T_ID;
                }
                else
                {
                    m_BuffRecv[0] = m_BuffRecv[1] ;
                    m_BuffRecv[1] = m_BuffRecv[2] ;
                    m_BuffRecv[2] = m_BuffRecv[3] ;
                    g_nRevCnt = 3;
                }
            }
            break;
        case T_ID:
            //g_nRevCnt++;  //4,5
            if(g_nRevCnt>=6)
            {
                Flag = T_LEN;
                break;
            }
            break;
        case T_LEN:
            //g_nRevCnt++;
            if(g_nRevCnt>=8) //6,7
            {
                u2Len = m_BuffRecv[6] + (m_BuffRecv[7]<<8)&0xFFFF;  //帧长度赋给 u2Len

                if((0 == m_BuffRecv[5])&&(0x1F == m_BuffRecv[4]))  //31帧
                    Flag = T31;
                else if((0 == m_BuffRecv[5])&&(0x20 == m_BuffRecv[4]))
                    Flag = T32;
                else if((0 == m_BuffRecv[5])&&(0x21 == m_BuffRecv[4]))
                    Flag = T33;
                else if((0 == m_BuffRecv[5])&&(0x22 == m_BuffRecv[4]))
                    Flag = T34;
                else if((0 == m_BuffRecv[5])&&(0x23 == m_BuffRecv[4]))
                    Flag = T35;
                else if((0 == m_BuffRecv[5])&&(0x24 == m_BuffRecv[4]))
                    Flag = T36;


                else
                {
                    g_nRevCnt = 0;  //异常：帧ID没有对上
                    Flag = GNSS;
                }
                break;
            }
            break;

        case T31:
        case T32:
        case T33:
        case T34:
        case T35:
        case T36:
            if(g_nRevCnt >= (u2Len+12))  //整帧数据接收完毕
            {
                if((0x0D == m_BuffRecv[g_nRevCnt-2])&&(0x0A == m_BuffRecv[g_nRevCnt-1]))  //校验帧尾
                {
                    u2 u2Sum = u2CheckSum(&m_BuffRecv[8],u2Len);
                    u2 u2Sum1 = (m_BuffRecv[u2Len+9]<<8)&0xFFFF;
                    if((u2)(u2Sum1 + m_BuffRecv[u2Len+8]) == u2Sum )
                    {
                        g_nRevCnt = 0;
                        Flag = GNSS;
                        return (int)m_BuffRecv[4];
                    }
                    else
                    {
                        //异常：没有通过校验和
                        g_nRevCnt = 0;
                        Flag = GNSS;
                    }
                }
                else
                {
                    //异常：没有对上帧尾
                    g_nRevCnt = 0;
                    Flag = GNSS;
                }

            }
            break;
        default:
            g_nRevCnt = 0;
            Flag = GNSS;
            break;

        }
        return 0;  //必须return 0。不然的话当switch语句break时会返回上一次的结果，解帧显示错误
}


