/* Analysis pseudo-C, not buildable source. */

void FUN_800303ec(void)

{
  undefined4 uVar1;
  int iVar2;
  
  DAT_8009c67a = 0x80;
  DAT_8009c673 = 0;
  DAT_8009c678 = 0;
  uVar1 = FUN_80036184(1,0xf,0x10,0x10,0x120,0xa0);
  FUN_800399f0(uVar1);
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,4);
  DAT_8009c65c = iVar2;
  FUN_80042b0c(iVar2,0);
  *(undefined1 *)(iVar2 + 0x45) = 0xc0;
  *(undefined1 *)(iVar2 + 0x3d) = 0xc0;
  *(undefined1 *)(iVar2 + 0x35) = 0xc0;
  *(undefined1 *)(iVar2 + 0x2d) = 0xc0;
  FUN_8003031c();
  FUN_8001591c();
  return;
}

