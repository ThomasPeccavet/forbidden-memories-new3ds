/* Analysis pseudo-C, not buildable source. */

void FUN_800852b8(void)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_800ff456 == 0) {
    psVar3 = &DAT_800ff3b8;
    iVar5 = (int)DAT_800ff3c8;
    if (DAT_800ff454 == 0) {
      psVar3 = &DAT_800ff3ba;
    }
    sVar1 = *psVar3;
    psVar3 = &DAT_800ff3bc;
    iVar4 = (int)DAT_800ff3ca;
    if (DAT_800ff454 == 0) {
      psVar3 = &DAT_800ff3be;
    }
    sVar2 = *psVar3;
    FUN_80087838(iVar5 + sVar1,iVar4 + sVar2);
    DAT_800ff444 = (undefined2)(iVar5 + sVar1);
    DAT_800ff446 = (undefined2)(iVar4 + sVar2);
  }
  else {
    DAT_800ff446 = 0;
    DAT_800ff444 = 0;
    DAT_800ff3d8 = DAT_800ff3c8 + (&DAT_800ff3b8)[DAT_800ff454];
    DAT_800ff3da = DAT_800ff3ca + (&DAT_800ff3bc)[DAT_800ff454];
    FUN_800802c8(&DAT_800ff3d0);
  }
  return;
}

