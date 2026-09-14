/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80086c78(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int local_a8 [14];
  int local_70 [14];
  int local_38 [12];
  undefined4 local_8;
  
  piVar2 = local_a8;
  uVar3 = 0;
  piVar6 = local_38;
  piVar5 = &DAT_80096468;
  piVar4 = local_70;
  local_a8[0] = 0x1000;
  local_70[0] = param_1;
  local_38[0] = 0;
  do {
    piVar6 = piVar6 + 1;
    piVar4 = piVar4 + 1;
    iVar1 = piVar2[0xe];
    if (iVar1 < 0) {
      piVar2[1] = *piVar2 - (iVar1 >> (uVar3 & 0x1f));
      *piVar4 = piVar2[0xe] + (*piVar2 >> (uVar3 & 0x1f));
      iVar1 = piVar2[0x1c] - *piVar5;
    }
    else {
      piVar2[1] = *piVar2 + (iVar1 >> (uVar3 & 0x1f));
      *piVar4 = piVar2[0xe] - (*piVar2 >> (uVar3 & 0x1f));
      iVar1 = piVar2[0x1c] + *piVar5;
    }
    *piVar6 = iVar1;
    piVar5 = piVar5 + 1;
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 1;
  } while ((int)uVar3 < 0xc);
  return local_8;
}

