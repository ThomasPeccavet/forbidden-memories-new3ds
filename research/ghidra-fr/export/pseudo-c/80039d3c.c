/* Analysis pseudo-C, not buildable source. */

void FUN_80039d3c(int param_1)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = FUN_80039a88();
  if (iVar4 == 0) {
    *(undefined1 *)(param_1 + 0x15) = 0;
    *(undefined1 *)(param_1 + 0x13) = 3;
    bVar1 = FUN_8008f708();
    if (0x7f < bVar1) {
      *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) | 0x40;
    }
    *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_1 + 2);
    *(undefined2 *)(param_1 + 8) = *(undefined2 *)(param_1 + 4);
    uVar2 = FUN_8008f708();
    *(ushort *)(param_1 + 10) = uVar2 & 0xfff;
    *(undefined2 *)(param_1 + 0xc) = 0x100;
    if ((*(byte *)(param_1 + 0x12) & 0x80) != 0) {
      *(undefined1 *)(param_1 + 0x15) = 0x80;
      *(undefined2 *)(param_1 + 0xc) = 0;
    }
  }
  uVar2 = (ushort)*(byte *)(param_1 + 0x12);
  if ((*(byte *)(param_1 + 0x12) & 0x80) == 0) {
    uVar6 = *(ushort *)(param_1 + 0xc) - 10;
    if ((int)uVar6 < 1) {
      *(short *)(param_1 + 2) = *(short *)(param_1 + 6);
      sVar3 = *(short *)(param_1 + 8);
      *(undefined1 *)(param_1 + 0x13) = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
      goto LAB_80039f00;
    }
  }
  else {
    uVar6 = *(ushort *)(param_1 + 0xc) + 10;
    uVar2 = uVar2 & 0x7f;
    if (0x13f < uVar6) {
      FUN_80039ab0(param_1);
      return;
    }
  }
  *(short *)(param_1 + 0xc) = (short)uVar6;
  uVar5 = uVar6;
  if (0xa0 < (int)uVar6) {
    uVar5 = 0xa0;
  }
  *(char *)(param_1 + 0x15) = (char)((int)((0xa0 - uVar5) * 0x80) / 0xa0);
  if ((uVar2 & 0x40) == 0) {
    uVar2 = *(short *)(param_1 + 10) + uVar2;
  }
  else {
    uVar2 = *(short *)(param_1 + 10) - (uVar2 & 0x3f);
  }
  uVar2 = uVar2 & 0xfff;
  *(ushort *)(param_1 + 10) = uVar2;
  iVar4 = FUN_800866f8(uVar2);
  iVar4 = iVar4 * uVar6;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xfff;
  }
  *(short *)(param_1 + 2) = *(short *)(param_1 + 6) + (short)(iVar4 >> 0xc);
  iVar4 = FUN_80086628(uVar2);
  iVar4 = iVar4 * uVar6;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xfff;
  }
  sVar3 = *(short *)(param_1 + 8) + (short)(iVar4 >> 0xc);
LAB_80039f00:
  *(short *)(param_1 + 4) = sVar3;
  return;
}

