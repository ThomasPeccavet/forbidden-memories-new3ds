/* Analysis pseudo-C, not buildable source. */

void FUN_8007d304(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  if (param_2 == (undefined1 *)0x0) {
    if (param_1 != (undefined1 *)0x0) {
      *param_1 = 0;
    }
  }
  else {
    iVar2 = 0;
    if (param_1 != (undefined1 *)0x0) {
      do {
        uVar1 = *param_2;
        param_2 = param_2 + 1;
        iVar2 = iVar2 + 1;
        *param_1 = uVar1;
        param_1 = param_1 + 1;
      } while (iVar2 < 8);
    }
  }
  return;
}

