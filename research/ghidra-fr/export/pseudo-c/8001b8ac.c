/* Analysis pseudo-C, not buildable source. */

void FUN_8001b8ac(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  DAT_8009c5b0 = (uint)DAT_8009c504 * 0x70 + -0x7ff14c38;
  (&DAT_800eb3e1)[(uint)DAT_8009c504 * 0x70] = 0;
  *(undefined1 *)(DAT_8009c5b0 + 0x13) = 1;
  iVar3 = DAT_8009c5b0;
  *(undefined2 *)(DAT_8009c5b0 + 0xc) = 0x84;
  *(undefined1 *)(iVar3 + 0x18) = 0;
  *(undefined1 *)(DAT_8009c5b0 + 0x11) = 2;
  *(undefined1 *)(DAT_8009c5b0 + 0x12) = 3;
  if (*(char *)(param_1 + 0x15) == '\0') {
    uVar2 = (int)(&DAT_801d4244)
                 [*(short *)(&DAT_801a7adc)
                            [(uint)*(byte *)((&DAT_800eb2b8)[*(char *)(param_1 + 0xe) * 3] + 0x6a) *
                             7] + -1] >> 0x1a & 0x1f;
    if ((0x13 < uVar2) &&
       ((*(char *)((&DAT_800eb2b8)[*(char *)(param_1 + 0xe) * 3] + 0x21) != '\0' || (uVar2 == 0x15))
       )) {
      *(undefined1 *)(DAT_8009c5b0 + 0x11) = 3;
      *(undefined1 *)(DAT_8009c5b0 + 0x12) = 4;
    }
  }
  *(undefined1 *)(DAT_8009c5b0 + 0x10) = *(undefined1 *)(DAT_8009c5b0 + 0x11);
  iVar3 = 0;
  puVar1 = &DAT_801a7ad8 +
           (uint)(byte)(&DAT_800919e0)
                       [*(char *)(DAT_8009c5b0 + 0x10) * 5 + (uint)DAT_8009c504 * 0x14] * 7;
  do {
    if ((*(ushort *)((int)puVar1 + 0x16) & 0x8000) == 0) {
      *(char *)(DAT_8009c5b0 + 0xf) = (char)iVar3;
      DAT_8009c57e = 3;
      return;
    }
    iVar3 = iVar3 + 1;
    puVar1 = puVar1 + 7;
  } while (iVar3 < 5);
  DAT_8009c57e = 3;
  return;
}

