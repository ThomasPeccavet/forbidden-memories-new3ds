/* Analysis pseudo-C, not buildable source. */

short * FUN_8006c2d0(short *param_1,short *param_2,short *param_3,short *param_4,int param_5)

{
  undefined4 uVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  short local_48;
  short local_46;
  short local_44;
  short local_40;
  short local_3e;
  short local_3c;
  short local_38;
  short local_36;
  short local_34;
  short local_30;
  short local_2e;
  short local_2c;
  short local_28;
  short local_26;
  short local_24;
  short local_20;
  short local_1e;
  short local_1c;
  
  local_48 = *param_1;
  local_46 = param_1[1];
  local_44 = param_1[2];
  local_40 = *param_2;
  local_3e = param_2[1];
  local_3c = param_2[2];
  local_38 = *param_3;
  local_36 = param_3[1];
  local_34 = param_3[2];
  iVar3 = (uint)(ushort)(*param_2 + *param_3) << 0x10;
  iVar4 = (uint)(ushort)(param_2[1] + param_3[1]) << 0x10;
  local_30 = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  local_2e = (short)((iVar4 >> 0x10) - (iVar4 >> 0x1f) >> 1);
  iVar3 = (uint)(ushort)(param_2[2] + param_3[2]) << 0x10;
  local_2c = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  iVar3 = (uint)(ushort)(*param_3 + *param_1) << 0x10;
  iVar4 = (uint)(ushort)(param_3[1] + param_1[1]) << 0x10;
  local_28 = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  local_26 = (short)((iVar4 >> 0x10) - (iVar4 >> 0x1f) >> 1);
  iVar3 = (uint)(ushort)(param_3[2] + param_1[2]) << 0x10;
  local_24 = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  param_5 = param_5 + -1;
  iVar3 = (uint)(ushort)(*param_1 + *param_2) << 0x10;
  iVar4 = (uint)(ushort)(param_1[1] + param_2[1]) << 0x10;
  local_20 = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  local_1e = (short)((iVar4 >> 0x10) - (iVar4 >> 0x1f) >> 1);
  iVar3 = (uint)(ushort)(param_1[2] + param_2[2]) << 0x10;
  local_1c = (short)((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1);
  if (param_5 == 0) {
    *param_4 = local_48;
    param_4[1] = local_46;
    param_4[2] = local_44;
    param_4[4] = local_20;
    param_4[5] = local_1e;
    param_4[6] = local_1c;
    param_4[8] = local_28;
    param_4[9] = local_26;
    param_4[10] = local_24;
    param_4[0xc] = local_40;
    param_4[0xd] = local_3e;
    param_4[0xe] = local_3c;
    param_4[0x10] = local_30;
    param_4[0x11] = local_2e;
    param_4[0x12] = local_2c;
    param_4[0x14] = local_20;
    param_4[0x15] = local_1e;
    param_4[0x16] = local_1c;
    param_4[0x18] = local_38;
    param_4[0x19] = local_36;
    param_4[0x1a] = local_34;
    param_4[0x1c] = local_28;
    param_4[0x1d] = local_26;
    param_4[0x1e] = local_24;
    param_4[0x20] = local_30;
    param_4[0x21] = local_2e;
    param_4[0x22] = local_2c;
    param_4[0x24] = local_30;
    param_4[0x25] = local_2e;
    param_4[0x26] = local_2c;
    param_4[0x28] = local_28;
    param_4[0x29] = local_26;
    param_4[0x2a] = local_24;
    param_4[0x2c] = local_20;
    param_4[0x2d] = local_1e;
    psVar2 = param_4 + 0x30;
    param_4[0x2e] = local_1c;
  }
  else {
    uVar1 = FUN_8006c2d0(&local_48,&local_20,&local_28,param_4,param_5);
    uVar1 = FUN_8006c2d0(&local_40,&local_30,&local_20,uVar1,param_5);
    uVar1 = FUN_8006c2d0(&local_38,&local_28,&local_30,uVar1,param_5);
    psVar2 = (short *)FUN_8006c2d0(&local_30,&local_28,&local_20,uVar1,param_5);
  }
  return psVar2;
}

