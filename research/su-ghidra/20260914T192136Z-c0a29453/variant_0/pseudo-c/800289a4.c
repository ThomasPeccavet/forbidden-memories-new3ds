/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800289a4(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_8009c5dc != 0) {
    if ((DAT_8009c5dc & 0x80) == 0) {
      DAT_8009c5d0 = DAT_8009c5dc;
      DAT_8009c5dc = DAT_8009c5dc | 0x80;
      DAT_8009c5de = 0;
      uVar1 = 1;
    }
    else if ((DAT_8009c5dc & 0x40) == 0) {
      (*(code *)(&PTR_FUN_80091f54)[DAT_8009c5d0])();
      uVar1 = 1;
    }
    else {
      DAT_8009c5dc = 0;
      uVar1 = 0;
    }
  }
  return uVar1;
}

