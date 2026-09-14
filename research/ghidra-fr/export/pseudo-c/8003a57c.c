/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003a57c(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  
  if (*(char *)(param_1 + 0x3c) == '\0') {
    uVar7 = 0xfffffff2;
    puVar4 = &DAT_801af000;
    uVar6 = 0x1d;
    uVar5 = 0x200;
  }
  else {
    uVar7 = 0xfffffff6;
    puVar4 = &DAT_801af800;
    uVar6 = 0x1a;
    uVar5 = 0x202;
  }
  iVar1 = FUN_8003a528(puVar4,param_3,0,0);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_80040350();
    iVar1 = FUN_800403d0(uVar2,2);
    FUN_80042bd8(iVar1,(int)*(short *)(param_1 + 0x34),(int)*(short *)(param_1 + 0x36),param_3,0,0,
                 uVar6,uVar5,puVar4);
    FUN_80042c48(iVar1);
    FUN_80042c1c(iVar1,uVar7);
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x41000000;
    *(ushort *)(iVar1 + 8) = *(ushort *)(iVar1 + 8) | 8;
    *param_2 = iVar1;
    iVar1 = FUN_8003a528(puVar4,param_3,1,0);
    iVar3 = 0;
    if (iVar1 != 0) {
      uVar2 = FUN_80040350();
      iVar3 = FUN_800403d0(uVar2,2);
      FUN_80042bd8(iVar3,(int)*(short *)(param_1 + 0x34),(int)*(short *)(param_1 + 0x36),param_3,1,0
                   ,uVar6,uVar5,puVar4);
      FUN_80042c48(iVar3);
      FUN_80042c1c(iVar3,uVar7 | 1);
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x41000000;
      *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 8;
    }
    param_2[1] = iVar3;
    iVar1 = FUN_8003a528(puVar4,param_3,2,0);
    iVar3 = 0;
    if (iVar1 != 0) {
      uVar2 = FUN_80040350();
      iVar3 = FUN_800403d0(uVar2,2);
      FUN_80042bd8(iVar3,(int)*(short *)(param_1 + 0x34),(int)*(short *)(param_1 + 0x36),param_3,2,0
                   ,uVar6,uVar5,puVar4);
      FUN_80042c48(iVar3);
      FUN_80042c1c(iVar3,uVar7 | 1);
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x41000000;
      *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 8;
    }
    param_2[2] = iVar3;
    uVar2 = 1;
  }
  return uVar2;
}

