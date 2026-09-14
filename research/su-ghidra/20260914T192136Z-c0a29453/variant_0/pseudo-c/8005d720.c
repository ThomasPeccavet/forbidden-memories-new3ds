/* Analysis pseudo-C, not buildable source. */

int FUN_8005d720(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_8004f1b4(*(byte *)((int)&DAT_800f4e78 +
                                param_1 * 0xe20 + (uint)(byte)(&DAT_800f4f76)[param_1 * 0xe20] + 2)
                       & 0x1f);
  iVar3 = (int)*(short *)(iVar1 + 2);
  iVar1 = iVar3 + 0x1400;
  if (param_1 < 1) {
    iVar1 = iVar3 + 0x1c00;
    iVar2 = iVar1;
    if (iVar1 < 0) {
      iVar2 = iVar3 + 0x2bff;
    }
  }
  else {
    iVar2 = iVar1;
    if (iVar1 < 0) {
      iVar2 = iVar3 + 0x23ff;
    }
  }
  return iVar1 + (iVar2 >> 0xc) * -0x1000;
}

