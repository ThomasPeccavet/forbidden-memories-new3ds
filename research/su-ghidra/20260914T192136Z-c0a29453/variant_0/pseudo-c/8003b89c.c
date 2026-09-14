/* Analysis pseudo-C, not buildable source. */

void FUN_8003b89c(undefined4 param_1)

{
  byte *pbVar1;
  undefined *puVar2;
  int iVar3;
  
  puVar2 = &DAT_800ec2a8;
  iVar3 = 2;
  pbVar1 = &DAT_800ec2db;
  do {
    if (-1 < (char)pbVar1[-3]) {
      if ((pbVar1[-1] & 0x40) != 0) {
        FUN_8003b708(puVar2,param_1);
      }
      if (*pbVar1 != 0) {
        (*(code *)(&PTR_LAB_80092394)[*pbVar1 & 0x1f])(puVar2);
      }
    }
    pbVar1 = pbVar1 + 0x4c;
    iVar3 = iVar3 + -1;
    puVar2 = puVar2 + 0x4c;
  } while (-1 < iVar3);
  return;
}

