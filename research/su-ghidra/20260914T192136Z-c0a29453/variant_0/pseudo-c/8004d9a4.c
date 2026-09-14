/* Analysis pseudo-C, not buildable source. */

void FUN_8004d9a4(int param_1,undefined2 param_2,int param_3,int param_4,short *param_5,
                 undefined4 param_6)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  short local_30;
  short local_2e;
  short local_2c;
  ushort local_2a;
  undefined2 local_28;
  short local_26;
  short local_24;
  undefined2 local_22;
  
  iVar3 = FUN_8005c310();
  FUN_8008f548(&local_30,0,8);
  local_2a = (ushort)param_1 | 0x80;
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    if (param_1 == 2) {
      FUN_8005c0b8(2,&local_30);
      local_2a = 1;
    }
    cVar1 = DAT_8009c312;
    if (param_5 != (short *)0x0) {
      sVar6 = -1;
      if (param_1 < 1) {
        sVar6 = 1;
      }
      local_30 = local_30 + *param_5 * sVar6;
      local_2e = local_2e + param_5[1];
      local_2c = local_2c + param_5[2] * sVar6;
    }
    if (param_1 < 1) {
      iVar4 = *(short *)(iVar3 + 2) + -0xc00;
    }
    else {
      iVar4 = *(short *)(iVar3 + 2) + -0x400;
    }
    iVar4 = (param_3 + 0x1000) - iVar4;
    iVar5 = iVar4;
    if (iVar4 < 0) {
      iVar5 = iVar4 + 0xfff;
    }
    local_26 = (short)iVar4 + (short)(iVar5 >> 0xc) * -0x1000;
    if (0x800 < local_26) {
      local_26 = local_26 + -0x1000;
    }
    if (local_26 < -0x800) {
      local_26 = local_26 + 0x1000;
    }
    iVar5 = param_4 + 0x1000;
    iVar4 = iVar5;
    if (iVar5 < 0) {
      iVar4 = param_4 + 0x1fff;
    }
    iVar3 = (iVar5 + (iVar4 >> 0xc) * -0x1000) - (uint)*(ushort *)(iVar3 + 4);
    local_24 = (short)iVar3;
    if (0x800 < iVar3 * 0x10000 >> 0x10) {
      local_24 = local_24 + -0x1000;
    }
    if (local_24 < -0x800) {
      local_24 = local_24 + 0x1000;
    }
    local_22 = 4;
    cVar2 = DAT_8009c312 + '\x01';
    if (DAT_8009c312 < '\0') {
      cVar2 = DAT_8009c312;
    }
    DAT_8009c312 = cVar2;
    local_28 = param_2;
    FUN_8004f92c('\0' < cVar1,&local_28,&local_30,param_6);
  }
  return;
}

