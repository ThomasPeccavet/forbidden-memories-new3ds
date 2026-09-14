/* Analysis pseudo-C, not buildable source. */

uint FUN_8004bfc4(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_8004bf74();
  uVar2 = 0;
  if (uVar1 != 0) {
    if (uVar1 == 0xff) {
      *(undefined1 *)(param_1 + 0x24) = 1;
      uVar2 = 0;
    }
    else {
      uVar2 = uVar1;
      if ((uVar1 & 0x80) != 0) {
        uVar2 = uVar1 & 0x7f;
        do {
          uVar1 = FUN_8004bf74(param_1);
          uVar2 = uVar2 * 0x80 + (uVar1 & 0x7f);
        } while ((uVar1 & 0x80) != 0);
      }
    }
  }
  return uVar2;
}

