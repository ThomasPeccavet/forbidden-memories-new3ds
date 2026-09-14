/* Analysis pseudo-C, not buildable source. */

undefined * FUN_80035fe8(int param_1,undefined2 param_2,ushort param_3)

{
  int iVar1;
  ushort uVar2;
  
  iVar1 = param_1 * 100;
  *(undefined2 *)(&DAT_800f0886 + iVar1) = param_2;
  uVar2 = param_3 & 3;
  (&DAT_800f0884)[param_1 * 0x32] = param_3 | 0x8000;
  (&DAT_800f08a7)[iVar1] = (char)param_1;
  (&DAT_800f08a4)[iVar1] = 0;
  *(undefined2 *)(&DAT_800f0888 + iVar1) = 0;
  *(undefined2 *)(&DAT_800f088a + iVar1) = 0;
  (&DAT_800f08aa)[iVar1] = 8;
  (&DAT_800f08ab)[iVar1] = 0x10;
  if (uVar2 == 2) {
    (&DAT_800f08aa)[iVar1] = 0xc;
  }
  else {
    if (uVar2 < 3) {
      if (uVar2 == 1) {
        (&DAT_800f08aa)[iVar1] = 8;
        (&DAT_800f08ab)[iVar1] = 8;
      }
      goto LAB_80036094;
    }
    if (uVar2 != 3) goto LAB_80036094;
    (&DAT_800f08aa)[iVar1] = 0x10;
  }
  (&DAT_800f08ab)[iVar1] = 0x10;
LAB_80036094:
  (&DAT_800f08a3)[iVar1] = 1;
  (&DAT_800f08a9)[iVar1] = 0;
  *(undefined2 *)(&DAT_800f08b2 + iVar1) = 0;
  *(short *)(&DAT_800f08ac + iVar1) = *(short *)(&DAT_80092264 + param_1 * 2);
  *(short *)(&DAT_800f08ae + iVar1) =
       *(short *)(&DAT_80092266 + param_1 * 2) - *(short *)(&DAT_80092264 + param_1 * 2);
  return &DAT_800f0850 + iVar1;
}

