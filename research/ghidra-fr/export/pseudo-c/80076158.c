/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80076158(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = DAT_80093fb8;
  if (param_1 == 0) {
    DAT_80093f4c = 0;
    *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xff7f;
    *(undefined2 *)(iVar2 + 0x184) = 0;
    *(undefined2 *)(iVar2 + 0x186) = 0;
    DAT_80093f60 = 0;
    DAT_80093f62 = 0;
  }
  else if (param_1 == 1) {
    if ((DAT_80093f50 == 1) || (iVar2 = FUN_800762c8(DAT_80093f54), iVar2 == 0)) {
      uVar1 = *(ushort *)(DAT_80093fb8 + 0x1aa) | 0x80;
      DAT_80093f4c = 1;
    }
    else {
      DAT_80093f4c = 0;
      uVar1 = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xff7f;
    }
    *(ushort *)(DAT_80093fb8 + 0x1aa) = uVar1;
  }
  return DAT_80093f4c;
}

