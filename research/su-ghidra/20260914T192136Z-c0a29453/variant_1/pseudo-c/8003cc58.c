/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003cc58(void)

{
  byte bVar1;
  int iVar2;
  short sVar3;
  undefined4 uVar4;
  
  iVar2 = DAT_8009c700;
  FUN_80042d30(DAT_8009c700);
  if (*(short *)(iVar2 + 0x5a) == 0) {
    bVar1 = *(byte *)(iVar2 + 0x6c);
    if (bVar1 == 1) {
      FUN_80042d08(iVar2);
      FUN_80040734(iVar2,2);
      *(undefined1 *)(iVar2 + 0x6c) = 2;
    }
    else if (bVar1 < 2) {
      if (bVar1 == 0) {
        FUN_80040734(iVar2,1);
        *(undefined1 *)(iVar2 + 0x6c) = 1;
        *(undefined2 *)(iVar2 + 0x36) = 0xff40;
      }
    }
    else if (bVar1 == 2) {
      FUN_80040734(iVar2,0);
      *(undefined1 *)(iVar2 + 0x6c) = 0;
      if (*(short *)(iVar2 + 0x30) < -0x2f) {
        *(undefined2 *)(iVar2 + 0x30) = 0x160;
        sVar3 = FUN_80035dfc(0xb0);
        *(short *)(iVar2 + 0x32) = sVar3 + 0x30;
      }
    }
  }
  uVar4 = 1;
  if (((DAT_800eb24e & 0x80) == 0) && (uVar4 = 0, (DAT_8009c72c & 0xe0) == 0)) {
    uVar4 = 1;
  }
  return uVar4;
}

