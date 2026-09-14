/* Analysis pseudo-C, not buildable source. */

void FUN_800341f8(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  
  uVar2 = FUN_80086dd8(param_1 * param_1 + param_3 * param_3);
  DAT_8009c690[1] = uVar2;
  iVar3 = FUN_80089928(param_1,param_3);
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xf;
  }
  uVar2 = (ushort)((iVar3 >> 4) << 8);
  if (0xff < iVar3 >> 4) {
    uVar2 = 0xff00;
  }
  uVar1 = (ushort)DAT_8009c694;
  *DAT_8009c690 = uVar2 | (ushort)(param_2 >> 4);
  DAT_8009c690[2] = uVar1;
  DAT_8009c690[3] = 0;
  DAT_8009c690 = DAT_8009c690 + 4;
  DAT_8009c694 = DAT_8009c694 + 1;
  return;
}

