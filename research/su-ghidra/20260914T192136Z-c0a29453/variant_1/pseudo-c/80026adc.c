/* Analysis pseudo-C, not buildable source. */

void FUN_80026adc(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_80024ee0();
  iVar2 = 0;
  if (iVar1 == 0) {
    iVar1 = FUN_8002c860(0x17);
    *(undefined2 *)(iVar1 + 4) = *(undefined2 *)(&DAT_80091a0a + (DAT_8009c504 ^ 1) * 0x50);
  }
  else {
    do {
      if (((&DAT_801a7aee)[(uint)(byte)(&DAT_800919e0)[iVar2 + (uint)DAT_8009c504 * 0x14] * 0xe] &
          0x8000) != 0) {
        FUN_80024a10();
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 5);
    DAT_8009c550 = 0;
  }
  return;
}

