/* Analysis pseudo-C, not buildable source. */

void FUN_80038d20(int param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  
  uVar1 = FUN_80036dfc();
  if ((uVar1 & 0x4000) == 0) {
    uVar2 = FUN_80036dfc(param_1);
    iVar3 = FUN_8002ce7c(uVar1);
    if (iVar3 != 0) {
      puVar4 = (uint *)(param_1 + *(char *)(param_1 + 0x58) * 4);
      *puVar4 = *puVar4 & 0xffff0000 | uVar2 & 0xffff;
    }
  }
  else {
    FUN_8002ceb8(uVar1 & 0xbfff);
  }
  return;
}

