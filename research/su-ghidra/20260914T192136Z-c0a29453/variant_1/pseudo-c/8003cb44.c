/* Analysis pseudo-C, not buildable source. */

void FUN_8003cb44(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,3);
  FUN_80040844(iVar2,0,0,0x140,0x100,0,0,0x10,0x280,0xd0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x1000000;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80042bd8(iVar2,0x1c0,0xc0,0,0,0,0x12,1,&DAT_801af000);
  *(undefined1 *)(iVar2 + 0x5e) = 0x80;
  FUN_80042c1c(iVar2,4);
  *(undefined1 *)(iVar2 + 0x6c) = 0;
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
  FUN_80042d08(iVar2);
  DAT_8009c700 = iVar2;
  FUN_8004022c(0x7300);
  FUN_800156f8();
  DAT_800eb24f = 2;
  return;
}

