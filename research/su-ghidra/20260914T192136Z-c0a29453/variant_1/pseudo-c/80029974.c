/* Analysis pseudo-C, not buildable source. */

void FUN_80029974(int param_1,undefined4 param_2,int param_3,int param_4,short param_5,int param_6)

{
  int iVar1;
  
  iVar1 = param_6 * 3;
  *(short *)(param_3 + 4) = param_5 + (short)param_6;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  *(short *)(param_3 + 0xc) = param_5 + (short)(iVar1 >> 2);
  *(short *)(param_3 + 0x14) = param_5;
  FUN_800879d8(param_3,param_3 + 8,param_3 + 0x10,param_1 + 8,param_1 + 0x10,param_1 + 0x18,param_4,
               param_4 + 4);
  if (*(int *)(param_4 + 4) < 0) {
    *(short *)(param_3 + 4) = param_5 + (short)(param_6 / 2);
    iVar1 = (param_6 / 2) * 3;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 3;
    }
    *(short *)(param_3 + 0xc) = param_5 + (short)(iVar1 >> 2);
    FUN_800879d8(param_3,param_3 + 8,param_3 + 0x10,param_1 + 8,param_1 + 0x10,param_1 + 0x18,
                 param_4,param_4 + 4);
  }
  FUN_8004d5b8(param_1,param_2,1,1);
  return;
}

