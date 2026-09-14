/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8002fca4(void)

{
  byte bVar1;
  uint uVar2;
  
  FUN_8008f708();
  if ((DAT_8009c628 & 0x4000) == 0) {
    if (DAT_8009c628 != 0) {
      if ((DAT_8009c628 & 0x8000) == 0) {
        uVar2 = (uint)*(ushort *)((int)&DAT_801a8000 + (uint)DAT_8009c628 * 2);
        DAT_8009c628 = DAT_8009c628 | 0x8000;
        DAT_8009c624 = (byte *)((int)&DAT_801a8000 + uVar2 + 1);
        DAT_8009c622 = 0;
        DAT_8009c610 = (ushort)*(byte *)((int)&DAT_801a8000 + uVar2);
      }
      if (DAT_8009c622 != 0) {
        DAT_8009c610 = DAT_8009c622;
      }
      while ((*(code *)(&PTR_FUN_80092068)[DAT_8009c610 & 0x1f])(), DAT_8009c610 == 0) {
        bVar1 = *DAT_8009c624;
        DAT_8009c624 = DAT_8009c624 + 1;
        DAT_8009c610 = (ushort)bVar1;
      }
    }
  }
  else {
    FUN_80039770();
    if ((_DAT_800f0884 & 0x2010) == 0x2000) {
      DAT_8009c628 = DAT_8009c628 & 0xbfff;
    }
  }
  return;
}

