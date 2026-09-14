/* Analysis pseudo-C, not buildable source. */

void FUN_8002e2f8(int *param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,0,0,2,0,0,param_2,param_3);
  FUN_80042c1c(iVar2,(int)(char)param_3);
  *(undefined1 *)(param_1 + 4) = 1;
  uVar4 = 0x1000000;
  if (param_3 == 2) {
    *(undefined2 *)(param_1 + 1) = 1;
    uVar3 = *(uint *)(iVar2 + 4);
    uVar4 = 0x50000000;
  }
  else {
    *(undefined2 *)(param_1 + 1) = 0;
    uVar3 = *(uint *)(iVar2 + 4);
  }
  *(uint *)(iVar2 + 4) = uVar3 | uVar4;
  *param_1 = iVar2;
  return;
}

