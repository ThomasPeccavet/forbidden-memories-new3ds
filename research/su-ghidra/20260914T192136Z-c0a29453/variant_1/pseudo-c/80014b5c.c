/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_80014b5c(uint *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_1 == (uint *)0x0) {
    puVar1 = (undefined4 *)(DAT_8009c460 & 0x20);
  }
  else {
    iVar3 = (int)(short)param_1[7];
    if ((param_1[5] == 0 && param_1[6] == 0) && iVar3 == 0) {
      puVar1 = (undefined4 *)FUN_800139b0(*param_1,param_1[1]);
    }
    else if (iVar3 == 0) {
      iVar3 = param_1[5] + param_1[6];
      puVar1 = (undefined4 *)0x0;
      if (iVar3 != 0) {
        uVar4 = *param_1;
        DAT_801d4220 = *param_1;
        DAT_801d4224 = param_1[1];
        DAT_801d4228 = param_1[2];
        DAT_801d422c = param_1[3];
        DAT_801d4230 = param_1[4];
        DAT_801d4234 = param_1[5];
        DAT_801d4238 = param_1[6];
        DAT_801d423c = param_1[7];
        uVar5 = param_1[1];
        uVar2 = DAT_8009c460 & 0xffffffdf;
        if (((DAT_8009c460 & 0x10) != 0) && ((DAT_8009c460 & 0x80000) != 0)) {
          DAT_8009c460 = uVar2;
          FUN_80014f2c();
          uVar2 = DAT_8009c460;
        }
        DAT_8009c460 = uVar2;
        puVar1 = &DAT_800eb200;
        FUN_800138b4(&DAT_800eb200,uVar4 | 0x1400000,param_2,uVar5,-iVar3,FUN_80014a4c,0,param_1);
        DAT_8009c460 = DAT_8009c460 | 0x20;
      }
    }
    else if (iVar3 < 0) {
      puVar1 = (undefined4 *)0x1;
      DAT_8009c47c = DAT_8009c47c & 0x3ffc | 2;
    }
    else {
      puVar1 = (undefined4 *)
               FUN_80013a84(DAT_800eb1b0 + param_1[1],DAT_800eb1b0 + param_1[1] + iVar3,
                            *(undefined1 *)((int)param_1 + 0x1f),
                            *(undefined1 *)((int)param_1 + 0x1e));
    }
  }
  return puVar1;
}

