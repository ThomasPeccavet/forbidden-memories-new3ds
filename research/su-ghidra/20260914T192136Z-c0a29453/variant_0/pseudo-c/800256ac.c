/* Analysis pseudo-C, not buildable source. */

void FUN_800256ac(void)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  undefined2 *puVar4;
  
  iVar2 = FUN_80024ee0();
  if (iVar2 == 0) {
    DAT_8009c4e4 = -1;
  }
  if ((DAT_8009c550 & 0x40) == 0) {
    DAT_8009c4e4 = DAT_8009c4e4 + 1;
    if (DAT_8009c4e4 < 5) {
      puVar4 = (undefined2 *)FUN_8002c7d8(0xc);
      iVar2 = (DAT_8009c4e4 + 5) * 4 + (uint)DAT_8009c504 * 0x50;
      uVar1 = *(undefined2 *)(&DAT_80091a08 + iVar2);
      DAT_8009c598 = puVar4;
      puVar4[1] = 0;
      *puVar4 = uVar1;
      puVar4[2] = *(undefined2 *)(&DAT_80091a0a + iVar2);
      FUN_80040204(0x20);
      DAT_8009c550 = DAT_8009c550 | 0x40;
    }
    else {
      DAT_8009c550 = 0;
    }
  }
  else {
    if (((DAT_8009c550 & 0x20) == 0) && (*(char *)((int)DAT_8009c598 + 0x1d) != '\0')) {
      uVar3 = (uint)(byte)(&DAT_800919e5)[(int)DAT_8009c4e4 + (uint)DAT_8009c504 * 0x14];
      if ((*(uint *)(&DAT_801a7aec + uVar3 * 0xe) & 0x88000000) == 0x88000000) {
        FUN_80019b30((&DAT_801a7ad8)[uVar3 * 7],0xc0,0,6);
        (&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] & 0xf7ff;
      }
      DAT_8009c550 = DAT_8009c550 | 0x20;
    }
    if ((*(byte *)(DAT_8009c598 + 0xe) & 0x80) == 0) {
      DAT_8009c550 = DAT_8009c550 & 0xff9f;
    }
  }
  return;
}

