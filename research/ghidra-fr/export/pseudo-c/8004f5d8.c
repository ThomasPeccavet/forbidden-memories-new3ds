/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8004f6bc) */
/* WARNING: Removing unreachable block (ram,0x8004f6cc) */
/* WARNING: Removing unreachable block (ram,0x8004f6d4) */

void FUN_8004f5d8(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_28 [6];
  short local_22;
  
  param_2 = param_2 * 8;
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    uVar1 = *(ushort *)(&DAT_80092454 + param_2);
    iVar4 = (int)((uint)uVar1 << 0x10) >> 0x10;
    if (param_1 < 2) {
      FUN_8005c108(param_1,auStack_28);
      if (local_22 < 0x32) {
        local_22 = 0x32;
      }
      local_22 = local_22 + -300;
      iVar3 = (int)local_22;
      if (iVar3 != 0) {
        iVar2 = iVar4;
        if (0 < iVar3) {
          iVar2 = iVar4 - ((int)((uint)uVar1 << 0x10) >> 0x1f) >> 1;
        }
        iVar4 = iVar4 + (iVar3 * iVar2) / 0x2ee;
      }
    }
    FUN_8004d9a4(param_1,iVar4,(int)*(short *)(&DAT_80092456 + param_2),
                 (int)*(short *)(&DAT_80092458 + param_2),param_3,param_4);
  }
  return;
}

