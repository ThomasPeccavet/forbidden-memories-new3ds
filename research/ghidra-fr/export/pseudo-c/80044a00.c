/* Analysis pseudo-C, not buildable source. */

int FUN_80044a00(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  if (0 < param_2) {
    do {
      uVar2 = *(uint *)(param_1 + 0x18);
      uVar1 = uVar2;
      if ((int)uVar2 < 0) {
        uVar1 = uVar2 + 0x1fff;
      }
      iVar3 = iVar3 + ((int)uVar1 >> 0xd);
      if ((uVar2 & 0x1fff) != 0) {
        iVar3 = iVar3 + 1;
      }
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 0x28;
    } while (iVar4 < param_2);
  }
  return 0xf - iVar3;
}

