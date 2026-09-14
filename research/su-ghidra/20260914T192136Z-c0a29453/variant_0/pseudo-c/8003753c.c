/* Analysis pseudo-C, not buildable source. */

void FUN_8003753c(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    DAT_8009c6de = 10;
    uVar1 = FUN_8003748c();
    *(undefined4 *)(param_1 + 0x30) = uVar1;
  }
  else {
    if ((DAT_8009c710 & 0x80) == 0) {
      DAT_8009c6de = 10;
    }
    else {
      DAT_8009c6de = DAT_8009c6de - 1;
      if ((int)((uint)DAT_8009c6de << 0x18) < 0) {
        DAT_8009c6de = 0;
      }
    }
    if ((DAT_8009c6de == 0) || ((DAT_8009c72c & 0xc0) != 0)) {
      FUN_80040204(0xb);
      *(undefined1 *)(param_1 + 0x51) = 2;
      FUN_80040690(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
  }
  return;
}

