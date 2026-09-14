/* Analysis pseudo-C, not buildable source. */

void FUN_8002416c(int param_1)

{
  byte bVar1;
  int iVar2;
  
  if ((DAT_8009c5c0 & 0x80) == 0) {
    DAT_8009c5c0 = DAT_8009c5c0 | 0xc0;
    *(undefined1 *)(param_1 + 0x12) = 4;
    *(undefined2 *)(param_1 + 0xc) = 0x84;
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x11) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    DAT_8009c57e = 3;
  }
  if ((DAT_8009c5c0 & 0x40) == 0) {
    iVar2 = FUN_8002411c(param_1);
    if (iVar2 == 0) {
      iVar2 = FUN_80016f50(&DAT_801a7ad8 +
                           (uint)(byte)(&DAT_800919e0)
                                       [*(char *)(param_1 + 0x10) * 5 +
                                        (int)*(char *)(param_1 + 0xf) + (uint)DAT_8009c504 * 0x14] *
                           7);
      if (iVar2 == 0) {
        if ((DAT_8009c710 & 3) == 0) {
          DAT_8009c57e = 0xc;
          DAT_8009c5c0 = DAT_8009c5c0 | 0x60;
        }
      }
      else {
        DAT_8009c5d8 = (undefined2)iVar2;
        DAT_8009c5dd = 0x14;
        DAT_8009c5dc = 2;
      }
    }
  }
  else if ((DAT_8009c57e == 0) &&
          (bVar1 = DAT_8009c5c0 & 0x20, DAT_8009c5c0 = DAT_8009c5c0 & 0xbf, bVar1 != 0)) {
    DAT_8009c5c0 = 0;
  }
  return;
}

