/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80070ef0(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = &DAT_800f6f70;
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    if ((int)(char)(&DAT_801ab008)[param_1 * 0xc] == (byte)puVar1[0x7e] - 1) {
      return 1;
    }
    puVar1 = &DAT_800f6f71 + iVar2;
    iVar2 = iVar3;
  } while (iVar3 < 0x19);
  return 0;
}

