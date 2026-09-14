/* Analysis pseudo-C, not buildable source. */

int FUN_8005d4d8(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar2 = (uint)*(byte *)(param_1 + 0xe17);
  iVar5 = 0;
  if (uVar2 != 0) {
    iVar7 = 0;
    iVar6 = *(int *)(param_1 + 0xd14);
    do {
      iVar3 = 0;
      if ((*(int *)(iVar6 + 0x4c) == param_2) && (uVar2 != 0)) {
        iVar1 = *(int *)(param_1 + 0xd14);
        iVar4 = iVar1 + iVar7;
        do {
          if (*(int *)(iVar1 + 0x4c) == iVar4) break;
          iVar3 = iVar3 + 1;
          iVar1 = iVar1 + 0x50;
        } while (iVar3 < (int)uVar2);
        if (iVar3 < (int)(uint)*(byte *)(param_1 + 0xe17)) {
          return iVar5;
        }
      }
      iVar7 = iVar7 + 0x50;
      uVar2 = (uint)*(byte *)(param_1 + 0xe17);
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 0x50;
    } while (iVar5 < (int)uVar2);
  }
  return iVar5;
}

