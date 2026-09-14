/* Analysis pseudo-C, not buildable source. */

void FUN_800194f4(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,1);
  FUN_80040844(iVar2,(int)*(short *)(param_1 + 0x30),(int)*(short *)(param_1 + 0x32),0x8c,0xd4,0,0,
               0x15,0,0);
  *(undefined2 *)(iVar2 + 0x18) = 0x46;
  *(undefined2 *)(iVar2 + 0x48) = 0x46;
  *(undefined2 *)(iVar2 + 0x1a) = 0x6a;
  *(undefined2 *)(iVar2 + 0x4a) = 0x6a;
  FUN_80042c48(iVar2);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x2000000;
  return;
}

