/* Analysis pseudo-C, not buildable source. */

void FUN_8008b0a8(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = FUN_8008b194();
  iVar2 = FUN_8008b25c(uVar1);
  uVar3 = iVar2 - 0xf;
  if (iVar2 < 0x10) {
    *param_2 = *param_1;
    param_2[1] = param_1[1];
    param_2[2] = param_1[2];
    param_2[3] = param_1[3];
    param_2[4] = param_1[4];
    iVar2 = param_1[5];
  }
  else {
    *param_2 = *param_1 >> (uVar3 & 0x1f);
    param_2[1] = param_1[1] >> (uVar3 & 0x1f);
    param_2[2] = param_1[2] >> (uVar3 & 0x1f);
    param_2[3] = param_1[3] >> (uVar3 & 0x1f);
    param_2[4] = param_1[4] >> (uVar3 & 0x1f);
    iVar2 = param_1[5] >> (uVar3 & 0x1f);
  }
  param_2[5] = iVar2;
  return;
}

