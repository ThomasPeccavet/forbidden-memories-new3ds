/* Analysis pseudo-C, not buildable source. */

void FUN_80022fa8(int param_1)

{
  int iVar1;
  
  iVar1 = (&DAT_800eb390)[(uint)DAT_8009c504 * 0x1c + *(short *)(param_1 + 0x2c) * 7];
  if (iVar1 == 0) {
    FUN_80040690(param_1);
  }
  else {
    *(short *)(param_1 + 0x30) = *(short *)(iVar1 + 0x30) + *(short *)(param_1 + 0x28);
    *(short *)(param_1 + 0x32) = *(short *)(iVar1 + 0x32) + *(short *)(param_1 + 0x2a);
    if (*(char *)(iVar1 + 0x6c) == '\0') {
      *(undefined1 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
  }
  return;
}

