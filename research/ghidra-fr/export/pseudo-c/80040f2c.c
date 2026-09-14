/* Analysis pseudo-C, not buildable source. */

void FUN_80040f2c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  sVar1 = DAT_800f11c6;
  while (iVar2 = (int)sVar1, -1 < iVar2) {
    iVar3 = iVar2 * 0x70;
    sVar1 = *(short *)(&DAT_800f1212 + iVar3);
    if (*(code **)(&DAT_800f1234 + iVar3) != (code *)0x0) {
      (**(code **)(&DAT_800f1234 + iVar3))(&DAT_800f1210 + iVar3);
    }
    if (((&DAT_800f1218)[iVar2 * 0x38] & 0xc0) == 0xc0) {
      FUN_80040c04(&DAT_800f1210 + iVar3,
                   *(undefined4 *)(&DAT_8009c858 + (uint)(byte)(&DAT_800f1227)[iVar3] * 4),
                   (int)*(short *)(&DAT_800f1224 + iVar3));
    }
  }
  return;
}

