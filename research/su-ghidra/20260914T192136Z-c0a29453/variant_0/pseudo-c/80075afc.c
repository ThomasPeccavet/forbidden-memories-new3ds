/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80075afc(int param_1,uint param_2,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  undefined4 uVar4;
  
  if (param_1 == 1) {
    DAT_80094008 = 0;
    if (*(short *)(DAT_80093fb8 + 0x1a6) != DAT_80093fd0) {
      uVar2 = 1;
      do {
        if (0xf00 < uVar2) {
          DAT_80094008 = 0;
          return 0xfffffffe;
        }
        uVar2 = uVar2 + 1;
      } while (*(short *)(DAT_80093fb8 + 0x1a6) != DAT_80093fd0);
    }
    *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xffcf | 0x20;
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      DAT_80094008 = 1;
      if (*(short *)(DAT_80093fb8 + 0x1a6) != DAT_80093fd0) {
        uVar2 = 1;
        do {
          if (0xf00 < uVar2) {
            DAT_80094008 = 1;
            return 0xfffffffe;
          }
          uVar2 = uVar2 + 1;
        } while (*(short *)(DAT_80093fb8 + 0x1a6) != DAT_80093fd0);
      }
      *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) | 0x30;
    }
  }
  else if (param_1 == 2) {
    DAT_80093fd0 = (short)(param_2 >> (DAT_80093fe0 & 0x1f));
    *(short *)(DAT_80093fb8 + 0x1a6) = DAT_80093fd0;
  }
  else if (param_1 == 3) {
    uVar3 = 0x20;
    if (DAT_80094008 == 1) {
      uVar3 = 0x30;
    }
    uVar2 = 1;
    uVar1 = *(ushort *)(DAT_80093fb8 + 0x1aa);
    while ((uVar1 & 0x30) != uVar3) {
      if (0xf00 < uVar2) {
        return 0xfffffffe;
      }
      uVar2 = uVar2 + 1;
      uVar1 = *(ushort *)(DAT_80093fb8 + 0x1aa);
    }
    if (DAT_80094008 == 1) {
      FUN_80076008();
    }
    else {
      FUN_80075fe0();
    }
    DAT_80094010 = (param_3 >> 6) + (uint)((param_3 & 0x3f) != 0);
    DAT_8009400c = param_2;
    *DAT_80093fbc = param_2;
    *DAT_80093fc0 = DAT_80094010 << 0x10 | 0x10;
    uVar4 = 0x1000201;
    if (DAT_80094008 == 1) {
      uVar4 = 0x1000200;
    }
    *DAT_80093fc4 = uVar4;
  }
  return 0;
}

