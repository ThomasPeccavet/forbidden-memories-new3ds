/* Analysis pseudo-C, not buildable source. */

void FUN_8003031c(void)

{
  int iVar1;
  short sVar2;
  int iVar3;
  
  iVar1 = DAT_8009c65c;
  iVar3 = (int)DAT_8009c679;
  sVar2 = DAT_800f08f0;
  if (9 < iVar3) {
    sVar2 = DAT_800f08f0 + -0x10 +
            (short)(((int)((uint)DAT_800f08f2 << 0x10) >> 0x10) -
                    ((int)((uint)DAT_800f08f2 << 0x10) >> 0x1f) >> 1);
  }
  *(short *)(DAT_8009c65c + 0x38) = sVar2;
  *(short *)(iVar1 + 0x28) = sVar2;
  sVar2 = sVar2 + (short)(((int)((uint)DAT_800f08f2 << 0x10) >> 0x10) -
                          ((int)((uint)DAT_800f08f2 << 0x10) >> 0x1f) >> 1) + -0x10;
  *(short *)(iVar1 + 0x40) = sVar2;
  *(short *)(iVar1 + 0x30) = sVar2;
  sVar2 = DAT_800f08f4 + (short)((iVar3 % 10) * 0x1000000 >> 0x14);
  *(short *)(iVar1 + 0x32) = sVar2;
  *(short *)(iVar1 + 0x2a) = sVar2;
  *(short *)(iVar1 + 0x42) = sVar2 + 0x10;
  *(short *)(iVar1 + 0x3a) = sVar2 + 0x10;
  return;
}

