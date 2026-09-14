/* Analysis pseudo-C, not buildable source. */

void FUN_800715d4(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = FUN_80070bb8();
  iVar5 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  iVar4 = *(int *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  uVar3 = 0;
  if (0x13 < ((int)(&DAT_801d4244)[iVar5 + -1] >> 0x1a & 0x1fU)) {
    if (iVar4 == 0) {
      switch(iVar5) {
      case 0x157:
        uVar3 = 0x32;
        break;
      case 0x158:
        uVar3 = 100;
        break;
      case 0x159:
        uVar3 = 200;
        break;
      case 0x15a:
        uVar3 = 500;
        break;
      case 0x15b:
        uVar3 = 1000;
      }
    }
    goto switchD_80071704_default;
  }
  if (iVar4 == 1) {
LAB_800716c0:
    uVar3 = 1;
  }
  else if (iVar4 < 2) {
    if (iVar4 != 0) goto switchD_80071704_default;
    uVar3 = 0;
  }
  else {
    if (iVar4 != 2) goto switchD_80071704_default;
    iVar4 = FUN_8002cdc8(iVar5,0);
    iVar2 = FUN_8002cdc8(iVar5,1);
    if (iVar4 <= iVar2) goto LAB_800716c0;
    uVar3 = 0;
  }
  uVar3 = FUN_8002cdc8(iVar5,uVar3);
switchD_80071704_default:
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = uVar3;
  return;
}

