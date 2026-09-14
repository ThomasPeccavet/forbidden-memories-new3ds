/* Analysis pseudo-C, not buildable source. */

void FUN_8002eca0(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_8002e650();
  if (iVar1 == 0) {
    iVar2 = (int)(short)DAT_8009c612;
    iVar1 = ((int)DAT_8009c62a - (int)DAT_8009c4c0) * 0x10000;
    DAT_8009c618 = iVar1 / iVar2;
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    iVar1 = ((int)DAT_8009c62c - (int)DAT_8009c4c2) * 0x10000;
    DAT_8009c61c = iVar1 / iVar2;
    if (iVar2 == 0) {
      trap(0x1c00);
    }
    if ((iVar2 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    DAT_8009c644 = (int)DAT_8009c4c0 << 0x10 | 0x8000;
    DAT_8009c648 = (int)DAT_8009c4c2 << 0x10 | 0x8000;
  }
  DAT_8009c644 = DAT_8009c644 + DAT_8009c618;
  DAT_8009c4c0 = (short)(DAT_8009c644 >> 0x10);
  DAT_8009c648 = DAT_8009c648 + DAT_8009c61c;
  DAT_8009c4c2 = (short)(DAT_8009c648 >> 0x10);
  DAT_8009c612 = DAT_8009c612 - 1;
  if ((int)((uint)DAT_8009c612 << 0x10) < 1) {
    DAT_8009c610 = 0;
    DAT_8009c4c0 = DAT_8009c62a;
    DAT_8009c4c2 = DAT_8009c62c;
  }
  return;
}

