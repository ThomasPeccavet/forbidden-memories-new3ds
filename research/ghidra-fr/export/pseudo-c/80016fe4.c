/* Analysis pseudo-C, not buildable source. */

uint FUN_80016fe4(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (int)*(short *)(param_1 + 0xe) + (int)*(short *)(param_1 + 0x12) +
          (int)*(short *)(param_1 + 0x14);
  uVar4 = uVar3;
  if ((int)uVar3 < 0) {
    uVar4 = 0;
  }
  if (9999 < (int)uVar3) {
    uVar4 = 9999;
  }
  iVar1 = (int)*(short *)(param_1 + 0x10) + (int)*(short *)(param_1 + 0x12) +
          (int)*(short *)(param_1 + 0x14);
  iVar2 = iVar1;
  if (iVar1 < 0) {
    iVar2 = 0;
  }
  if (9999 < iVar1) {
    iVar2 = 9999;
  }
  return iVar2 << 0x10 | uVar4;
}

