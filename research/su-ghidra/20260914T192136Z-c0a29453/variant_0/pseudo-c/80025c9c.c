/* Analysis pseudo-C, not buildable source. */

void FUN_80025c9c(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_80024ee0();
  if (iVar1 == 0) {
    DAT_8009c598 = (undefined2 *)FUN_8002c7d8(0x13);
    *DAT_8009c598 = 0xa0;
    DAT_8009c598[1] = 0x68;
    FUN_80040204(0x13);
  }
  else {
    if (((DAT_8009c550 & 0x40) == 0) && (*(char *)((int)DAT_8009c598 + 0x1d) != '\0')) {
      DAT_8009c550 = DAT_8009c550 | 0x40;
      FUN_80040204(0x1d);
      iVar1 = 5;
      do {
        if ((*(uint *)(&DAT_801a7aec +
                      (uint)(byte)(&DAT_800919e0)[iVar1 + (uint)DAT_8009c504 * 0x14] * 0xe) &
            0x90000000) == 0x90000000) {
          iVar2 = (&DAT_801a7ad8)
                  [(uint)(byte)(&DAT_800919e0)[iVar1 + (uint)DAT_8009c504 * 0x14] * 7];
          *(code **)(iVar2 + 0x24) = FUN_80025bd8;
          *(undefined1 *)(iVar2 + 0x6c) = 1;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0xf);
    }
    if (((DAT_8009c5f8 & 1) == 0) && (iVar1 = FUN_80042e70(1), iVar1 == 0)) {
      DAT_8009c550 = 0;
    }
  }
  return;
}

