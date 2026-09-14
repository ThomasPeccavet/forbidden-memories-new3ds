/* Analysis pseudo-C, not buildable source. */

void FUN_80086978(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int local_60 [6];
  int local_48;
  int local_40 [6];
  int local_28;
  int local_20 [6];
  int local_8;
  
  piVar2 = local_60;
  uVar3 = 0;
  piVar6 = local_20;
  piVar5 = &DAT_80096448;
  piVar4 = local_40;
  local_60[0] = 0x9b7;
  local_40[0] = 0;
  local_20[0] = param_1;
  do {
    piVar6 = piVar6 + 1;
    piVar4 = piVar4 + 1;
    if (piVar2[0x10] < 0) {
      piVar2[1] = *piVar2 + (piVar2[8] >> (uVar3 & 0x1f));
      *piVar4 = piVar2[8] - (*piVar2 >> (uVar3 & 0x1f));
      iVar1 = piVar2[0x10] + *piVar5;
    }
    else {
      piVar2[1] = *piVar2 - (piVar2[8] >> (uVar3 & 0x1f));
      *piVar4 = piVar2[8] + (*piVar2 >> (uVar3 & 0x1f));
      iVar1 = piVar2[0x10] - *piVar5;
    }
    *piVar6 = iVar1;
    piVar5 = piVar5 + 1;
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 1;
  } while ((int)uVar3 < 6);
  *param_3 = local_48 - (local_8 * local_28 >> 0xc);
  *param_2 = local_28 + (local_8 * local_48 >> 0xc);
  return;
}

