/* Analysis pseudo-C, not buildable source. */

int FUN_80077628(uint param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0;
  uVar2 = 1;
  do {
    uVar5 = uVar4;
    if ((param_1 & uVar2) != 0) break;
    uVar4 = uVar4 + 1;
    uVar2 = 1 << (uVar4 & 0x1f);
    uVar5 = 0xffffffff;
  } while ((int)uVar4 < 0x18);
  iVar3 = -1;
  if (uVar5 != 0xffffffff) {
    sVar1 = *(short *)(uVar5 * 0x10 + DAT_80093fb8 + 0xc);
    if ((DAT_80093f44 & 1 << (uVar5 & 0x1f)) == 0) {
      iVar3 = (uint)(sVar1 != 0) << 1;
    }
    else {
      iVar3 = 1;
      if (sVar1 == 0) {
        iVar3 = 3;
      }
    }
  }
  return iVar3;
}

