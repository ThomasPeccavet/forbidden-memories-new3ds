/* Analysis pseudo-C, not buildable source. */

void FUN_8004f3c8(int param_1,undefined2 param_2,int param_3,int param_4,short *param_5)

{
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  short local_28;
  short local_26;
  short local_24;
  
  iVar1 = FUN_8005c304();
  puVar2 = (undefined2 *)FUN_8005c310();
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    if (-1 < param_1) {
      FUN_8005c0b8(param_1,&local_28);
      *(int *)(iVar1 + 0xc) = (int)local_28;
      *(int *)(iVar1 + 0x10) = (int)local_26;
      *(int *)(iVar1 + 0x14) = (int)local_24;
    }
    if (param_5 != (short *)0x0) {
      iVar3 = -1;
      if (param_1 < 1) {
        iVar3 = 1;
      }
      *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + *param_5 * iVar3;
      *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + (int)param_5[1];
      *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + param_5[2] * iVar3;
    }
    *puVar2 = param_2;
    if (param_1 < 1) {
      iVar3 = param_3 + 0x1c00;
      iVar1 = iVar3;
      if (iVar3 < 0) {
        iVar1 = param_3 + 0x2bff;
      }
    }
    else {
      iVar3 = param_3 + 0x1400;
      iVar1 = iVar3;
      if (iVar3 < 0) {
        iVar1 = param_3 + 0x23ff;
      }
    }
    puVar2[1] = (short)iVar3 + (short)(iVar1 >> 0xc) * -0x1000;
    iVar3 = param_4 + 0x1000;
    iVar1 = iVar3;
    if (iVar3 < 0) {
      iVar1 = param_4 + 0x1fff;
    }
    puVar2[2] = (short)iVar3 + (short)(iVar1 >> 0xc) * -0x1000;
    FUN_8005b5cc(1,0x1000,0,0,1);
    FUN_8004f080(1);
    FUN_8005cfc4(0xffffffff);
  }
  return;
}

