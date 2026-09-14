/* Analysis pseudo-C, not buildable source. */

void FUN_8003876c(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_80036dfc();
  if ((uVar1 & 0x8000) == 0) {
    FUN_80040204();
  }
  else {
    FUN_800402ac();
    DAT_8009c6b2 = FUN_80036dfc(param_1);
    *(undefined1 *)(param_1 + 0x51) = 0x11;
    DAT_8009c6cc = 1;
  }
  return;
}

