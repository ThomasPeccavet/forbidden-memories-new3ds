/* Analysis pseudo-C, not buildable source. */

void FUN_80078b18(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (param_2 != 0) {
    do {
      iVar1 = uVar2 + param_1;
      uVar2 = uVar2 + 1;
      *(undefined4 *)(DAT_800f70e4 + iVar1 * 0x20) = 0;
    } while (uVar2 < param_2);
  }
  return;
}

