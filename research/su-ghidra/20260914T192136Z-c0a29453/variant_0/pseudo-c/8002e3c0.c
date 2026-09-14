/* Analysis pseudo-C, not buildable source. */

void FUN_8002e3c0(int *param_1,uint param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  
  if ((int)param_2 < 0) {
    param_2 = (uint)(short)param_1[0xf];
  }
  *(short *)(param_1 + 0xf) = (short)param_2;
  if ((int)param_2 < 0x200) {
    FUN_8002e2f8(param_1,0x10,0);
    if ((int)param_2 < 0x100) {
      param_1[5] = 0;
      param_1[10] = 0;
    }
    else {
      iVar3 = (((int)param_2 >> 4 & 0xfU) * 10 + (param_2 & 0xf)) * 2;
      bVar1 = (&DAT_80091fc0)[iVar3];
      if ((bVar1 & 1) != 0) {
        FUN_8002e2f8(param_1 + 5,0x12,1);
      }
      if ((bVar1 & 2) != 0) {
        FUN_8002e2f8(param_1 + 10,0x14,2);
        *(ushort *)(param_1 + 0xb) = (ushort)(byte)(&DAT_80091fc1)[iVar3];
      }
    }
  }
  else {
    uVar2 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar2,3);
    FUN_80040844(iVar3,0,0,0x200,0x100,0,0,0x10,0x280,0xd0);
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x1000000;
    *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) & 0xfff7;
    iVar4 = (((int)param_2 >> 4 & 0xfU) * 10 + (param_2 & 0xf)) * 6;
    *(undefined1 *)(param_1 + 4) = 1;
    *param_1 = iVar3;
    pbVar5 = &DAT_80092018 + iVar4;
    *(undefined2 *)(param_1 + 1) = 0;
    if ((*pbVar5 & 1) != 0) {
      FUN_8002e2f8(param_1 + 5,0x14,1);
      *(ushort *)(param_1[5] + 0x30) = (ushort)(byte)(&DAT_80092019)[iVar4];
      *(ushort *)(param_1[5] + 0x32) = (ushort)(byte)(&DAT_8009201a)[iVar4];
    }
    if ((*pbVar5 & 2) != 0) {
      FUN_8002e2f8(param_1 + 10,0x16,2);
      *(ushort *)(param_1[10] + 0x30) = (ushort)(byte)(&DAT_8009201b)[iVar4];
      *(ushort *)(param_1[10] + 0x32) = (ushort)(byte)(&DAT_8009201c)[iVar4];
      *(ushort *)(param_1 + 0xb) = (ushort)(byte)(&DAT_8009201d)[iVar4];
      if ((*pbVar5 & 0x80) != 0) {
        *(ushort *)(param_1[10] + 8) = *(ushort *)(param_1[10] + 8) | 8;
      }
    }
  }
  return;
}

