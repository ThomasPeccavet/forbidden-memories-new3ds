/* Analysis pseudo-C, not buildable source. */

void FUN_80180ee4(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  if (iVar2 != 0) {
    FUN_80042bd8(iVar2,(int)*(short *)(param_1 + 0x30),(int)*(short *)(param_1 + 0x32),0,0,
                 *(undefined1 *)(param_1 + 0x69),0x18,0,&DAT_801af800);
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x51000000;
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x48;
    FUN_80042c48(iVar2);
    FUN_80042c1c(iVar2,(int)-*(char *)(param_1 + 0x60));
    *(code **)(iVar2 + 0x24) = FUN_80180fc8;
    *(undefined1 *)(iVar2 + 0xc) = *(undefined1 *)(param_1 + 0xc);
    *(undefined1 *)(iVar2 + 0xd) = *(undefined1 *)(param_1 + 0xd);
    *(undefined1 *)(iVar2 + 0xe) = *(undefined1 *)(param_1 + 0xe);
  }
  return;
}

