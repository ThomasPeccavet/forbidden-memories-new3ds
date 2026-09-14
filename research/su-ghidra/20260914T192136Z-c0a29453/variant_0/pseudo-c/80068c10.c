/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80068c10(undefined1 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_800f6c88;
  iVar2 = 0;
  if (param_1 == &LAB_80089da8) {
    return 0xffffffff;
  }
  do {
    iVar2 = iVar2 + 1;
    if ((undefined1 *)*puVar1 == param_1) {
      return puVar1[1];
    }
    puVar1 = puVar1 + 2;
  } while (iVar2 < 0x50);
  return 0xffffffff;
}

