/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004bbc4(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 1;
  if ((((*(char *)(DAT_8009c7d8 + 0x814) != '\0') &&
       (uVar1 = 1, *(char *)(DAT_8009c7d8 + 0x500) == '\0')) &&
      (uVar1 = 1, *(char *)(DAT_8009c7d8 + 0x509) == '\0')) &&
     (uVar1 = 0, *(char *)(DAT_8009c7d8 + 0x501) == '\0')) {
    FUN_80073f34(0xf2000002);
    iVar2 = 0;
    *(undefined1 *)(DAT_8009c7d8 + 0x501) = 1;
    do {
      FUN_8004cd58();
      *(char *)(DAT_8009c7d8 + 0x508) = *(char *)(DAT_8009c7d8 + 0x508) + '\x01';
      if (10 < *(byte *)(DAT_8009c7d8 + 0x508)) {
        *(undefined1 *)(DAT_8009c7d8 + 0x508) = 0;
        FUN_8004ccdc();
        FUN_8004af8c();
        if (*(code **)(DAT_8009c7d8 + 0x50c) != (code *)0x0) {
          (**(code **)(DAT_8009c7d8 + 0x50c))();
        }
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 8);
    *(undefined1 *)(DAT_8009c7d8 + 0x501) = 0;
    uVar1 = 0;
  }
  return uVar1;
}

