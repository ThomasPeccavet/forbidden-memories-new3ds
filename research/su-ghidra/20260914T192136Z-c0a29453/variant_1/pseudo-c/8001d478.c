/* Analysis pseudo-C, not buildable source. */

int FUN_8001d478(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = DAT_8009c528;
  if (DAT_8009c528 == 0) {
    uVar1 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar1,2);
    FUN_8004078c(iVar2,4,3,8,0xb,0x1f0);
    *(undefined1 *)(iVar2 + 0x6a) = *(undefined1 *)(param_1 + 10);
    FUN_80042c1c(iVar2,1);
    *(code **)(iVar2 + 0x24) = FUN_80015cd4;
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 8;
  }
  return iVar2;
}

