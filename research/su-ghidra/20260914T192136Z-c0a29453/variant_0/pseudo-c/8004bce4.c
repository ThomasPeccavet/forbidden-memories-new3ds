/* Analysis pseudo-C, not buildable source. */

void FUN_8004bce4(void)

{
  undefined4 uVar1;
  
  if (*(char *)(DAT_8009c7d8 + 0x503) == '\0') {
    *(undefined1 *)(DAT_8009c7d8 + 0x503) = 1;
    FUN_80073df8();
    FUN_80073f9c(0xf2000002);
    uVar1 = FUN_80073da8(0xf2000002,2,0x1000,FUN_8004bbc4);
    *(undefined4 *)(DAT_8009c7d8 + 0x504) = uVar1;
    FUN_80073dd8();
    FUN_80073e98(0xf2000002,0xe000,0x1000);
    FUN_80073f6c(0xf2000002);
    FUN_80073e08();
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 0;
    *(undefined1 *)(DAT_8009c7d8 + 0x503) = 0;
  }
  return;
}

