/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8004f368) */
/* WARNING: Removing unreachable block (ram,0x8004f378) */
/* WARNING: Removing unreachable block (ram,0x8004f380) */

void FUN_8004f28c(int param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_20 [6];
  short local_1a;
  
  param_2 = param_2 * 8;
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    uVar1 = *(ushort *)(&DAT_80092454 + param_2);
    iVar4 = (int)((uint)uVar1 << 0x10) >> 0x10;
    if (param_1 < 2) {
      FUN_8005c108(param_1,auStack_20);
      if (local_1a < 0x32) {
        local_1a = 0x32;
      }
      local_1a = local_1a + -300;
      iVar3 = (int)local_1a;
      if (iVar3 != 0) {
        iVar2 = iVar4;
        if (0 < iVar3) {
          iVar2 = iVar4 - ((int)((uint)uVar1 << 0x10) >> 0x1f) >> 1;
        }
        iVar4 = iVar4 + (iVar3 * iVar2) / 0x2ee;
      }
    }
    FUN_8004f3c8(param_1,iVar4,(int)*(short *)(&DAT_80092456 + param_2),
                 (int)*(short *)(&DAT_80092458 + param_2),param_3);
  }
  return;
}

