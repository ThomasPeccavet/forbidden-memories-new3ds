/* Analysis pseudo-C, not buildable source. */

int FUN_8002e698(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040390();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,0x10,0xb0,0,0,0,0xd,0x100);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 8;
  FUN_80042c48(iVar2);
  return iVar2;
}

