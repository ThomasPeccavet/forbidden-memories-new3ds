/* Analysis pseudo-C, not buildable source. */

uint FUN_80077fe8(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  
  iVar2 = (int)(((param_3 + ((param_4 + param_2 & 0xffffU) >> 7)) - param_1) * 0x10000) >> 0x10;
  sVar1 = (short)(iVar2 / 0xc);
  sVar4 = sVar1 + -2;
  iVar2 = iVar2 % 0xc;
  if (iVar2 * 0x10000 < 0) {
    iVar2 = iVar2 + 0xc;
    sVar4 = sVar1 + -3;
  }
  if (sVar4 < 0) {
    uVar3 = -(int)sVar4;
    uVar3 = (uint)(((int)((uint)*(ushort *)(&DAT_80094428 + ((iVar2 << 0x10) >> 0xf)) *
                         (uint)*(ushort *)((int)&PTR_DAT_80094440 + (param_4 + param_2 & 0x7fU) * 2)
                         ) >> 0x10) + (1 << (uVar3 - 1 & 0x1f))) >> (uVar3 & 0x1f);
  }
  else {
    uVar3 = 0x3fff;
  }
  return uVar3 & 0xffff;
}

