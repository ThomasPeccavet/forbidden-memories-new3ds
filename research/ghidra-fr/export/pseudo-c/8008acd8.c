/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_8008acd8(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined1 auStack_90 [20];
  undefined1 auStack_7c [12];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_30;
  int local_2c;
  int local_28;
  
  DAT_800ff4d0 = DAT_800ff510;
  DAT_800ff4d4 = DAT_800ff514;
  DAT_800ff4d8 = _DAT_800ff518;
  DAT_800ff4dc = DAT_800ff51c;
  DAT_800ff4e0 = DAT_800ff520;
  DAT_800ff4e4 = DAT_800ff524;
  DAT_800ff4e8 = DAT_800ff528;
  DAT_800ff4ec = DAT_800ff52c;
  FUN_80085e58(&DAT_800ff4d0,-param_1[6]);
  FUN_8008b0a8(param_1,&local_b0);
  iVar1 = FUN_80086dd8((local_a4 - local_b0) * (local_a4 - local_b0) +
                       (local_a0 - local_ac) * (local_a0 - local_ac) +
                       (local_9c - local_a8) * (local_9c - local_a8));
  uVar2 = 1;
  if (iVar1 != 0) {
    iVar4 = (local_ac - local_a0) * 0x1000;
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar4 == -0x80000000)) {
      trap(0x1800);
    }
    iVar3 = FUN_80086dd8((local_a4 - local_b0) * (local_a4 - local_b0) +
                         (local_9c - local_a8) * (local_9c - local_a8));
    if (iVar1 == 0) {
      trap(0x1c00);
    }
    if ((iVar1 == -1) && (iVar3 << 0xc == -0x80000000)) {
      trap(0x1800);
    }
    FUN_80086178(auStack_90,(int)(short)-(short)(iVar4 / iVar1),(int)(short)((iVar3 << 0xc) / iVar1)
                 ,0x78);
    FUN_800872f8(&DAT_800ff4d0,auStack_90);
    if (iVar3 != 0) {
      iVar1 = (local_a4 - local_b0) * 0x1000;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar1 == -0x80000000)) {
        trap(0x1800);
      }
      iVar4 = (local_9c - local_a8) * 0x1000;
      if (iVar3 == 0) {
        trap(0x1c00);
      }
      if ((iVar3 == -1) && (iVar4 == -0x80000000)) {
        trap(0x1800);
      }
      FUN_80086178(auStack_90,(int)(short)-(short)(iVar1 / iVar3),(int)(short)(iVar4 / iVar3),0x79);
      FUN_800872f8(&DAT_800ff4d0,auStack_90);
    }
    local_30 = -*param_1;
    local_2c = -param_1[1];
    local_28 = -param_1[2];
    FUN_80086ff8(&DAT_800ff4d0,&local_30,&DAT_800ff4e4);
    if (param_1[7] != 0) {
      FUN_8008a428(param_1[7],auStack_90);
      FUN_8008b278(auStack_90,&local_70);
      FUN_80086ff8(&local_70,auStack_7c,&local_30);
      local_5c = -local_30;
      local_54 = -local_28;
      local_58 = -local_2c;
      FUN_80086528(&DAT_800ff4d0,&local_70);
      DAT_800ff4d0 = local_70;
      DAT_800ff4d4 = local_6c;
      DAT_800ff4d8 = local_68;
      DAT_800ff4dc = local_64;
      DAT_800ff4e0 = local_60;
      DAT_800ff4e4 = local_5c;
      DAT_800ff4e8 = local_58;
      DAT_800ff4ec = local_54;
    }
    DAT_800ff4b0 = DAT_800ff4d0;
    DAT_800ff4b4 = DAT_800ff4d4;
    DAT_800ff4b8 = DAT_800ff4d8;
    DAT_800ff4bc = DAT_800ff4dc;
    DAT_800ff4c0 = DAT_800ff4e0;
    DAT_800ff4c4 = DAT_800ff4e4;
    DAT_800ff4c8 = DAT_800ff4e8;
    DAT_800ff4cc = DAT_800ff4ec;
    uVar2 = 0;
  }
  return uVar2;
}

