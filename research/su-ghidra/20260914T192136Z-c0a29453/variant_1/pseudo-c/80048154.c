/* Analysis pseudo-C, not buildable source. */

void FUN_80048154(undefined2 param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  sVar1 = FUN_800480e0(param_1);
  iVar3 = 0;
  uVar4 = (uint)*(byte *)(DAT_8009c7e0 + 0x435);
  uVar5 = 1 << (uVar4 & 0x1f);
  iVar2 = 1 << (uVar4 + 0x14 & 0x1f);
  do {
    if (((*(byte *)(DAT_8009c7e0 + 0x434) & uVar5) != 0) &&
       (*(short *)(DAT_8009c7e0 + uVar4 * 2 + 0x404) == sVar1)) {
      FUN_80048100(iVar2);
      *(char *)(DAT_8009c7e0 + 0x435) = (char)uVar4;
      *(byte *)(DAT_8009c7e0 + 0x434) = *(byte *)(DAT_8009c7e0 + 0x434) & ~(byte)uVar5;
      return;
    }
    uVar5 = uVar5 << 1;
    iVar2 = iVar2 << 1;
    if ((uVar5 & 0x10) != 0) {
      uVar5 = 1;
    }
    iVar3 = iVar3 + 1;
    uVar4 = uVar4 + 1 & 3;
  } while (iVar3 < 4);
  return;
}

