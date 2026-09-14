/* Analysis pseudo-C, not buildable source. */

void FUN_8018425c(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if ((&DAT_80185ec8)[param_1 * 0xb] != 0) {
    do {
      iVar1 = iVar1 + 1;
      FUN_80184324(param_1,(&DAT_80185ec8)[param_1 * 0xb + iVar1],param_2);
    } while (iVar1 < (int)(uint)(ushort)(&DAT_80185ec8)[param_1 * 0xb]);
  }
  return;
}

