/* Analysis pseudo-C, not buildable source. */

void FUN_8004a8cc(byte *param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = DAT_8009c7d8 + (uint)param_1[3] * 0x18;
  if (((ushort)*(byte *)(iVar4 + 7) != *(ushort *)(param_1 + 0x1a)) || (param_2 != 0)) {
    *(ushort *)(param_1 + 0x1a) = (ushort)*(byte *)(iVar4 + 7);
    iVar2 = FUN_8004a84c(param_1,*(undefined1 *)(iVar4 + 7));
    iVar4 = DAT_8009c7d8;
    uVar3 = iVar2 + (uint)param_1[6] * 0x80;
    *(undefined4 *)(DAT_8009c7d8 + 0x4c4) = 0x10;
    *(undefined4 *)(iVar4 + 0x4c0) = (&DAT_80011360)[*param_1];
    uVar1 = FUN_8004a444((int)(uVar3 * 0x10000) >> 0x17,uVar3 & 0x7f,param_1[0x12],param_1[0x13]);
    iVar4 = DAT_8009c7d8 + 0x4c0;
    *(undefined2 *)(DAT_8009c7d8 + 0x4d4) = uVar1;
    FUN_800779e8(iVar4);
  }
  return;
}

