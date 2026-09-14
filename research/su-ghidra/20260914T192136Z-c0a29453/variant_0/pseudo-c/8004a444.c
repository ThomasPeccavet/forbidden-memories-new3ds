/* Analysis pseudo-C, not buildable source. */

uint FUN_8004a444(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (param_2 + param_4) * 0x10000 >> 0x10;
  iVar1 = iVar2;
  if (iVar2 < 0) {
    iVar1 = iVar2 + 0x7f;
  }
  iVar2 = iVar2 + (iVar1 >> 7) * -0x80;
  param_3 = (param_1 + (iVar1 >> 7)) - param_3;
  iVar1 = param_3 * 0x10000 >> 0x10;
  if (iVar1 < 0) {
    iVar1 = param_3 * -0x10000 >> 0x10;
    return (int)(uint)*(ushort *)
                       (&DAT_80010760 +
                       (iVar2 * 0x10000 >> 0xf) +
                       ((0xc - ((iVar1 % 0xc) * 0x10000 >> 0x10)) % 0xc) * 0x100) >>
           ((iVar1 + 0xb) / 0xc & 0x1fU) & 0xffff;
  }
  return (uint)*(ushort *)
                (&DAT_80010760 + (iVar2 * 0x10000 >> 0xf) + ((iVar1 % 0xc) * 0x10000 >> 8)) <<
         (iVar1 / 0xc & 0x1fU) & 0xffff;
}

