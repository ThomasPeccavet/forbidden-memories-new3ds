/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80026e50(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int local_48;
  int local_44 [5];
  int local_30;
  int local_2c [5];
  
  piVar3 = &local_30;
  iVar1 = FUN_80026da0(piVar3,0,0x17);
  if (iVar1 != 0) {
    FUN_80026da0(&local_48,5,0xffffffff);
    iVar1 = local_48;
    iVar5 = local_30;
    while (local_48 = iVar1, iVar5 != 0) {
      if (iVar1 != 0) {
        piVar4 = &local_48;
        do {
          iVar2 = FUN_80019998((int)*(short *)(iVar5 + 0xc),(int)*(short *)(iVar1 + 0xc));
          piVar4 = piVar4 + 1;
          if (iVar2 != 0) {
            DAT_800ec210 = *(char *)(iVar5 + 0x18) % '\x05' + '\v';
            DAT_800ec211 = 0;
            DAT_800ec216 = *(char *)(iVar1 + 0x18) % '\x05' + '\x01';
            DAT_800ec217 = 0;
            DAT_800ec218 = 0;
            return 0;
          }
          iVar1 = *piVar4;
        } while (iVar1 != 0);
      }
      piVar3 = piVar3 + 1;
      iVar1 = local_48;
      iVar5 = *piVar3;
    }
    iVar1 = FUN_80026c94(5);
    if (iVar1 < 0) {
      return 1;
    }
    FUN_80026cf4(&local_48,0,0x14);
    piVar3 = &local_30;
    iVar5 = local_48;
    while (local_30 != 0) {
      local_48 = iVar5;
      if (iVar5 != 0) {
        piVar4 = &local_48;
        do {
          iVar2 = FUN_80019998((int)*(short *)(local_30 + 0xc),(int)*(short *)(iVar5 + 0xc));
          piVar4 = piVar4 + 1;
          if (iVar2 != 0) {
            DAT_800ec210 = *(char *)(iVar5 + 0x18) % '\x05' + '\v';
            DAT_800ec211 = *(char *)(local_30 + 0x18) % '\x05' + '\v';
            DAT_800ec212 = 0;
            DAT_800ec216 = (char)iVar1 + (char)(iVar1 / 5) * -5 + '\x01';
            DAT_800ec217 = 0;
            DAT_800ec218 = 0;
            return 0;
          }
          iVar5 = *piVar4;
        } while (iVar5 != 0);
      }
      piVar3 = piVar3 + 1;
      iVar5 = local_48;
      local_30 = *piVar3;
    }
  }
  return 1;
}

