#include "mex.h"
#include "dc_iir_fxp_c.h"


void dc_iir_fxp(INT32 *x, INT32 XLen, INT32 Num[3], INT32 Den[3], INT32 Pow2, INT32 WLen, INT32 *y)
{
    INT64 Reg0, Reg1, Reg2;
    INT32 ii;
    INT64 Tmp64;

    // init
    Reg0 = 0;
    Reg1 = 0;
    Reg2 = 0;
    // filter
    for (ii = 0; ii < XLen; ii++)
    {
        // Reg0
        Tmp64 = (INT64)Num[0] * ((INT64)x[ii]<<(WLen-16))
              + (Reg1<<(WLen-1));                       // Fwl=2WLen-2
        Reg0 = ROUND_LAST_KBIT(Tmp64<<Pow2, WLen-1);    // Fwl round to WLen-1
        Reg0 = SAT(Reg0, ((INT64)1<<(WLen-1))-1, ((INT64)-1<<(WLen-1)));
        y[ii] = ROUND_LAST_KBIT(Reg0,(WLen-16));
        // Reg1
        Tmp64 = (INT64)Num[1] * ((INT64)x[ii]<<(WLen-16))
              + (Reg2<<(WLen-1))
              - (INT64)Den[1] * (INT64)Reg0;            // Fwl=2WLen-2
        Reg1 = ROUND_LAST_KBIT(Tmp64, WLen-1);           // Fwl round to WLen-1
        Reg1 = SAT(Reg1, ((INT64)1<<(WLen-1))-1, ((INT64)-1<<(WLen-1)));
        // Reg2
        Tmp64 = (INT64)Num[2] * ((INT64)x[ii]<<(WLen-16))
              - (INT64)Den[2] * (INT64)Reg0;            // Fwl = (2*WLen-2)
        Reg2 = ROUND_LAST_KBIT(Tmp64, WLen-1);          // Fwl round to WLen-1
        Reg2 = SAT(Reg2, ((INT64)1<<(WLen-1))-1, ((INT64)-1<<(WLen-1)));
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{
    INT32 *x, XLen;
    INT32 Num[3];
    INT32 Den[3];
    INT32 Pow2;
    INT32 WLen; // word length in iir
    INT32 *pTmp32,ii;
    INT32 *y;

    x = (INT32 *)mxGetPr(prhs[0]);
    XLen = mxGetN(prhs[0]);
    pTmp32 = (INT32 *)mxGetPr(prhs[1]);
    for (ii = 0; ii < 3; ii++) {
        Num[ii] = pTmp32[ii];
    }
    pTmp32 = (INT32 *)mxGetPr(prhs[2]);
    for (ii = 0; ii < 3; ii++) {
        Den[ii] = pTmp32[ii];
    }
    Pow2 = *(INT32 *)mxGetPr(prhs[3]);
    WLen = *(INT32 *)mxGetPr(prhs[4]);

    plhs[0] = mxCreateNumericMatrix(1, XLen, mxINT32_CLASS, mxREAL);
    y = (INT32 *)mxGetPr(plhs[0]);
    dc_iir_fxp(x, XLen, Num, Den, Pow2, WLen, y);
}