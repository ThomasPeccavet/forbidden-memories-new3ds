/* Analysis pseudo-C, not buildable source. */

int FUN_80024cd8(int param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar2 = FUN_80040350();
  iVar3 = FUN_800403d0(uVar2,0);
  *(undefined2 *)(iVar3 + 0x32) = 0xffe8;
  *(undefined2 *)(iVar3 + 0x30) = param_2;
  *(undefined2 *)(iVar3 + 0x34) = param_3;
  *(undefined1 *)(iVar3 + 0x67) = 0;
  *(undefined1 *)(iVar3 + 0x69) = 0;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x1000000;
  iVar4 = (&DAT_801d4244)[param_1 + -1];
  *(undefined1 **)(iVar3 + 0x10) = &LAB_80016694;
  *(undefined1 *)(iVar3 + 0x5c) = 0;
  *(undefined1 *)(iVar3 + 0x5d) = 0xc0;
  *(undefined2 *)(iVar3 + 0x42) = 0;
  uVar5 = iVar4 >> 0x1a & 0x1f;
  *(char *)(iVar3 + 0x68) = (char)uVar5;
  if (uVar5 < 0x14) {
    return iVar3;
  }
  *(undefined1 *)(iVar3 + 0x5c) = 0x38;
  if (uVar5 == 0x15) {
    uVar1 = 2;
  }
  else if (uVar5 < 0x16) {
    uVar1 = 1;
    if (uVar5 != 0x14) {
      return iVar3;
    }
  }
  else {
    if (uVar5 != 0x16) {
      if (uVar5 != 0x17) {
        return iVar3;
      }
      *(undefined2 *)(iVar3 + 0x42) = 1;
      return iVar3;
    }
    uVar1 = 3;
  }
  *(undefined2 *)(iVar3 + 0x42) = uVar1;
  return iVar3;
}

