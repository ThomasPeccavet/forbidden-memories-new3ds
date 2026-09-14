/* Analysis pseudo-C, not buildable source. */

void FUN_800180e0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040390();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,param_1,param_2,0,1,0,0x1f,0x100);
  FUN_80042c48(iVar2);
  FUN_80042c1c(iVar2,0xfffffffe);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 8;
  return;
}

