/* Analysis pseudo-C, not buildable source. */

void FUN_8007795c(undefined1 *param_1)

{
  short sVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    sVar1 = *(short *)(uVar2 * 0x10 + DAT_80093fb8 + 0xc);
    if ((DAT_80093f44 & 1 << (uVar2 & 0x1f)) == 0) {
      if (sVar1 == 0) {
        *param_1 = 0;
      }
      else {
        *param_1 = 2;
      }
    }
    else if (sVar1 == 0) {
      *param_1 = 3;
    }
    else {
      *param_1 = 1;
    }
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 1;
  } while ((int)uVar2 < 0x18);
  return;
}

