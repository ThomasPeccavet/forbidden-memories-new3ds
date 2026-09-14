/* Analysis pseudo-C, not buildable source. */

bool FUN_80085f18(short *param_1,short param_2,short param_3,short param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)param_2;
  if (iVar3 != 0x1000) {
    *param_1 = (short)(*param_1 * iVar3 >> 0xc);
    param_1[3] = (short)(param_1[3] * iVar3 >> 0xc);
    param_1[6] = (short)(param_1[6] * iVar3 >> 0xc);
  }
  iVar1 = (int)param_3;
  if (iVar1 != 0x1000) {
    param_1[1] = (short)(param_1[1] * iVar1 >> 0xc);
    param_1[4] = (short)(param_1[4] * iVar1 >> 0xc);
    param_1[7] = (short)(param_1[7] * iVar1 >> 0xc);
  }
  iVar2 = (int)param_4;
  if (iVar2 != 0x1000) {
    param_1[2] = (short)(param_1[2] * iVar2 >> 0xc);
    param_1[5] = (short)(param_1[5] * iVar2 >> 0xc);
    param_1[8] = (short)(param_1[8] * iVar2 >> 0xc);
  }
  return iVar2 != 0x1000 || (iVar1 != 0x1000 || iVar3 != 0x1000);
}

