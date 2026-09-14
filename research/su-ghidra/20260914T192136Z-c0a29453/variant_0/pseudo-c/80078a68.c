/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80078a68(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  
  iVar1 = (param_1 - (DAT_800f70e4 + DAT_800f70f0 * 0x20) >> 2) / 0x1f8;
  psVar5 = (short *)(DAT_800f70e4 + iVar1 * 0x20);
  uVar2 = 1;
  if (*psVar5 == 4) {
    iVar3 = (int)psVar5[3];
    iVar6 = 0;
    if (0 < iVar3) {
      do {
        iVar4 = iVar6 + iVar1;
        iVar6 = iVar6 + 1;
        *(undefined2 *)(DAT_800f70e4 + iVar4 * 0x20) = 0;
      } while (iVar6 < iVar3);
    }
    DAT_800f70dc = iVar6 + iVar1;
    uVar2 = 0;
  }
  return uVar2;
}

