/* Analysis pseudo-C, not buildable source. */

void FUN_80025178(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  short sVar6;
  
  sVar1 = DAT_8009c5c4;
  iVar5 = (int)DAT_8009c5c4;
  sVar6 = DAT_8009c5c4 + -0x152;
  iVar2 = FUN_80024ee0();
  iVar3 = DAT_8009c500;
  if (iVar2 == 0) {
    iVar3 = FUN_800250d8(0x2b0);
    if (iVar3 != 0) {
      sVar6 = sVar1 + -0x14d;
    }
    puVar4 = (undefined2 *)FUN_8002c860(5);
    *puVar4 = 0xa0;
    puVar4[1] = 0x78;
    puVar4[0xd] = sVar6;
    FUN_80040204(0x14);
    return;
  }
  if ((DAT_8009c550 & 0x40) == 0) {
    if (DAT_8009c558 == 0) {
      iVar2 = (uint)*(ushort *)(DAT_8009c500 + 0x14) + (uint)(byte)(&DAT_8009c176)[iVar5] * 100;
      *(short *)(DAT_8009c500 + 0x14) = (short)iVar2;
      if (iVar2 * 0x10000 >> 0x10 <= (int)*(short *)(iVar3 + 0x16)) {
        DAT_8009c550 = 0;
        return;
      }
      *(undefined2 *)(iVar3 + 0x14) = *(undefined2 *)(iVar3 + 0x16);
      DAT_8009c550 = 0;
      return;
    }
    DAT_8009c520 = 0;
    DAT_8009c550 = DAT_8009c550 | 0x60;
  }
  if ((DAT_8009c550 & 0x20) == 0) {
    iVar2 = (uint)*(ushort *)(DAT_8009c500 + 0x14) + (uint)(byte)(&DAT_8009c176)[iVar5] * -100;
    *(short *)(DAT_8009c500 + 0x14) = (short)iVar2;
    if (iVar2 * 0x10000 < 0) {
      *(undefined2 *)(iVar3 + 0x14) = 0;
    }
    DAT_8009c550 = 0;
    return;
  }
  iVar3 = FUN_8001f2c4();
  if (iVar3 == 0) {
    DAT_8009c550 = DAT_8009c550 & 0xffdf;
    puVar4 = (undefined2 *)FUN_8002c860(9);
    *puVar4 = 0xa0;
    puVar4[1] = 0x78;
    puVar4[0xd] = sVar6;
    return;
  }
  return;
}

