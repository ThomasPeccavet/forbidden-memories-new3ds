/* Analysis pseudo-C, not buildable source. */

uint FUN_8005bc14(ushort *param_1,undefined4 param_2,int param_3,uint param_4,int param_5,
                 int param_6,int param_7,int param_8)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ushort local_30;
  ushort local_2e;
  ushort local_2c;
  ushort local_2a;
  
  uVar5 = 0;
  uVar4 = 0;
  iVar3 = FUN_8005c9ec(param_2,0x80400000);
  if (0 < iVar3) {
    FUN_80086088(0x80400004,param_1);
    uVar2 = (ushort)param_3;
    if (param_3 < 2) {
      if (*(int *)(param_1 + 2) == 0) {
        param_1[2] = 0xc0;
        param_1[3] = 0x100;
      }
      if (*(int *)(param_1 + 8) == 0) {
        param_1[8] = 0x280;
        param_1[9] = 0xf2;
      }
      if (param_5 < 0) {
        param_1[2] = param_1[2] + (uVar2 & 1) * 0x100;
      }
      else {
        param_1[2] = (ushort)param_5;
      }
      if (-1 < param_6) {
        param_1[3] = (ushort)param_6;
      }
      if (-1 < param_7) {
        param_1[8] = (ushort)param_7;
      }
      if (param_8 < 0) {
        param_1[9] = param_1[9] + uVar2;
      }
      else {
        param_1[9] = (ushort)param_8;
      }
    }
    else if (2 < param_3) {
      uVar2 = uVar2 - 3 & 1;
      sVar1 = uVar2 * 0x100;
      param_1[2] = (param_1[2] - 0x280) + sVar1;
      if ((short)param_1[9] < 0x100) {
        if (param_1[9] == 8) {
          param_1[9] = uVar2 + 0xf2;
        }
      }
      else {
        param_1[8] = (param_1[8] - 0x280) + sVar1;
      }
    }
    local_30 = param_1[2];
    local_2e = param_1[3];
    local_2c = param_1[4];
    local_2a = param_1[5];
    do {
      iVar3 = FUN_8008288c(3);
    } while (iVar3 != 0);
    do {
      iVar3 = FUN_80082380(&local_30,*(undefined4 *)(param_1 + 6));
    } while (iVar3 != 0);
    local_30 = param_1[8];
    local_2e = param_1[9];
    local_2c = param_1[10];
    local_2a = param_1[0xb];
    do {
      iVar3 = FUN_8008288c(3);
    } while (iVar3 != 0);
    do {
      iVar3 = FUN_80082380(&local_30,*(undefined4 *)(param_1 + 0xc));
    } while (iVar3 != 0);
    do {
      iVar3 = FUN_8008288c(3);
    } while (iVar3 != 0);
    uVar5 = (*param_1 & 3) << 7 | (param_4 & 3) << 5 | (int)((param_1[3] & 0x100) << 0x10) >> 0x14 |
            (param_1[2] & 0x3ff) >> 6 | (param_1[3] & 0x200) << 2;
    uVar4 = (uint)param_1[9] << 6 | param_1[8] >> 4 & 0x3f;
  }
  return uVar5 << 0x10 | uVar4 & 0xffff;
}

