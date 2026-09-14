/* Analysis pseudo-C, not buildable source. */

void FUN_800494a0(void)

{
  int iVar1;
  
  if (*(short *)(DAT_8009c7e0 + 0x157e) != -1) {
    if ((*(ushort *)(DAT_8009c7e0 + 0x40) & 0x80) != 0) {
      FUN_8004a0d0();
      *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) & 0xff7f;
    }
    FUN_8004a140((int)*(short *)(DAT_8009c7e0 + 0x157e));
    *(undefined2 *)(DAT_8009c7e0 + 0x157e) = 0xffff;
  }
  if (*(short *)(DAT_8009c7e0 + 0x157a) == 0) {
    FUN_80049d88(0);
    iVar1 = DAT_8009c7e0;
    *(undefined2 *)(DAT_8009c7e0 + 0x157a) = 0xffff;
    *(undefined2 *)(iVar1 + 0x1578) = 0xffff;
  }
  iVar1 = DAT_8009c7e0;
  *(undefined2 *)(DAT_8009c7e0 + 0x1588) = 0;
  *(undefined2 *)(iVar1 + 0x1586) = 0;
  return;
}

