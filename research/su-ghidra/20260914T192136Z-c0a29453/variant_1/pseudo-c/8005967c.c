/* Analysis pseudo-C, not buildable source. */

undefined4
FUN_8005967c(uint param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,
            undefined4 param_7)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_1 & 0x7f;
  if ((int)param_2 < 0) {
    param_2 = (uint)(ushort)(&DAT_800f4f70)[uVar3 * 0x710];
  }
  else {
    (&DAT_800f4f70)[uVar3 * 0x710] = (short)param_2;
  }
  if ((param_1 & 0x80) == 0) {
    FUN_80048354();
  }
  FUN_80013700();
  FUN_8004fc2c(uVar3,0,0,param_7);
  iVar2 = uVar3 * 0xe20;
  (&DAT_800f4f95)[iVar2] = (char)(param_1 & 0x80);
  if (uVar3 < 2) {
    if (param_2 == 0x309) {
      iVar1 = FUN_80014e08(1,s_M__mrgSU_SU_mrg_80011424,0x5d4,0x113,FUN_8005a92c,0,0);
      DAT_8009c460 = *(uint *)(iVar1 + 0x2c) | 0x10;
      (&DAT_800f4f8c)[iVar2] = 0;
      return 0;
    }
    if ((((param_2 < 0x2d2) && (0x31 < param_2 - 300)) && (0x31 < param_2 - 0x28a)) &&
       (param_2 != 0x2d0)) {
      if (0x2d0 < (int)param_2) {
        param_2 = param_2 - 1;
      }
      if (699 < (int)param_2) {
        param_2 = param_2 - 0x32;
      }
      if (0x15d < (int)param_2) {
        param_2 = param_2 - 0x32;
      }
      iVar1 = FUN_80014e08(2,s_M__mrgSU_model_mrg_800114ac,param_2 * 0x114,0x114,FUN_80059ef4,0,0);
      if (-1 < param_3) {
        *(short *)(&DAT_800f4f72 + iVar2) = (short)param_3;
      }
      if (-1 < param_4) {
        *(short *)(&DAT_800f4f74 + iVar2) = (short)param_4;
      }
      if (-1 < param_5) {
        (&DAT_800f4f76)[iVar2] = param_5 != 0;
      }
      if (-1 < param_6) {
        (&DAT_800f4f77)[iVar2] = param_6 != 0;
      }
      *(uint *)(iVar1 + 0x38) = uVar3;
      DAT_8009c460 = *(uint *)(iVar1 + 0x2c) | 0x10;
      *(uint *)(iVar1 + 0x3c) = (uint)(byte)(&DAT_800f4f76)[uVar3 * 0xe20];
      (&DAT_800f4f8c)[uVar3 * 0xe20] = 0;
      return 0;
    }
  }
  else if ((param_2 < 7) && ((byte)(&DAT_8009256c)[param_2 * 0xb2] < 7)) {
    iVar1 = FUN_80014e08(1,s_M__mrgSU_SU_mrg_80011424,
                         (uint)(byte)(&DAT_8009256c)[param_2 * 0xb2] * 0x74 + 0x2a8,0x74,
                         FUN_8005a6c0,0,0);
    DAT_8009c460 = *(uint *)(iVar1 + 0x2c) | 0x10;
    (&DAT_800f4f8c)[iVar2] = 0;
    return 0;
  }
  return 1;
}

