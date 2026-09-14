/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800150f4(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  bVar1 = DAT_800eb24f;
  uVar6 = (uint)DAT_800eb24f;
  if (DAT_800eb24c < DAT_800eb24d) {
    uVar5 = (uint)DAT_800eb250;
    iVar4 = 0xf;
    do {
      uVar5 = uVar5 - uVar6;
      uVar2 = uVar5;
      if ((int)uVar5 < (int)(uint)DAT_800eb24c) {
        uVar2 = (uint)DAT_800eb24c;
      }
      if ((int)(uint)DAT_800eb24d < (int)uVar2) {
        uVar2 = (uint)DAT_800eb24d;
      }
      iVar3 = iVar4 + -1;
      (&DAT_800eb252)[iVar4] = (char)uVar2;
      (&DAT_800eb271)[-iVar4] = (char)uVar2;
      iVar4 = iVar3;
    } while (-1 < iVar3);
    DAT_800eb250 = DAT_800eb250 + (ushort)bVar1 * (short)_DAT_8009c43c;
  }
  else {
    uVar5 = (uint)DAT_800eb250;
    iVar4 = 0;
    do {
      uVar5 = uVar5 + uVar6;
      uVar2 = uVar5;
      if ((int)uVar5 < (int)(uint)DAT_800eb24d) {
        uVar2 = (uint)DAT_800eb24d;
      }
      if ((int)(uint)DAT_800eb24c < (int)uVar2) {
        uVar2 = (uint)DAT_800eb24c;
      }
      iVar3 = iVar4 + 1;
      (&DAT_800eb252)[iVar4] = (char)uVar2;
      (&DAT_800eb271)[-iVar4] = (char)uVar2;
      iVar4 = iVar3;
    } while (iVar3 < 0x10);
    DAT_800eb250 = DAT_800eb250 - (ushort)bVar1 * (short)_DAT_8009c43c;
  }
  if (uVar2 == DAT_800eb24d) {
    DAT_800eb24c = (byte)uVar2;
  }
  return;
}

