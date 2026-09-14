/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_801835b8(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 local_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  
  bVar1 = (&DAT_80185ef8)[param_1];
  uVar6 = (uint)bVar1;
  local_28[0] = _FUN_80180004;
  local_28[1] = uRam80180008;
  local_28[2] = uRam8018000c;
  local_28[3] = uRam80180010;
  local_18 = uRam80180014;
  local_14 = uRam80180018;
  if ((param_2 != 0) || (uVar6 == 0)) {
    iVar5 = 0;
    iVar4 = param_1 * 0xb48;
    do {
      iVar2 = iVar5 + param_1 * 0x1000;
      sVar3 = 0;
      if ((&DAT_801d1250)[iVar2] != 0) {
        sVar3 = (short)iVar5 + 1;
      }
      *(short *)(&DAT_80184828 + iVar4) = sVar3;
      iVar5 = iVar5 + 1;
      *(ushort *)(&DAT_8018482a + iVar4) = (ushort)(byte)(&DAT_801d1250)[iVar2];
      iVar4 = iVar4 + 4;
    } while (iVar5 < 0x2d2);
    iVar4 = 0;
    do {
      FUN_8018425c(iVar4,0xffffffff);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    if (uVar6 == 0) goto LAB_80183704;
  }
  FUN_8008f578(&DAT_80184828 + param_1 * 0xb48,0x2d2,4,local_28[uVar6 - 1]);
LAB_80183704:
  *(byte *)((&DAT_801a8000)[param_1 * 7] + 0x69) = bVar1;
  return;
}

