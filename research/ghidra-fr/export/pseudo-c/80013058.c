/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80013058(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  FUN_8007f8e8(0);
  FUN_80084d58(0x140,0x100,4,1,0);
  FUN_80085628(0,0,0x140,0);
  DAT_800ff438 = CONCAT22(0x14,(undefined2)DAT_800ff438);
  DAT_800ff43c = CONCAT22(0x100,(undefined2)DAT_800ff43c);
  DAT_8009c456 = 1;
  DAT_8009c434 = 1;
  DAT_8009c44a = 0;
  DAT_8009c4be = 1;
  DAT_8009c4bb = 1;
  DAT_8009c4bd = 1;
  DAT_8009c4ba = 1;
  DAT_8009c4bc = 1;
  DAT_8009c4b9 = 1;
  DAT_800ff3e8 = 1;
  DAT_800ff3e6 = 1;
  DAT_800ff3e9 = 1;
  DAT_800ff3ea = 1;
  DAT_800ff3eb = 1;
  DAT_8009c430 = 2;
  DAT_8009c431 = 6;
  DAT_8009c432 = 0xc;
  DAT_8009c433 = 6;
  iVar1 = param_1;
  do {
    uVar2 = 3;
    iVar3 = 0x514c;
    *(undefined4 *)(iVar1 + 0x5110) = 2;
    *(int *)(iVar1 + 0x5128) = iVar1 + 0x10;
    *(undefined4 *)(iVar1 + 0x5138) = 0xc;
    *(int *)(iVar1 + 0x513c) = iVar1 + 0x110;
    *(int *)(iVar1 + 0x5114) = iVar1;
    *(undefined4 *)(iVar1 + 0x5124) = 6;
    *(undefined4 *)(iVar1 + 0x514c) = 6;
    *(int *)(iVar1 + 0x5150) = iVar1 + 0x4110;
    do {
      FUN_80085d38(0,uVar2 & 0xffff,iVar1 + iVar3);
      uVar2 = uVar2 - 1;
      iVar3 = iVar3 + -0x14;
    } while (-1 < (int)uVar2);
    iVar1 = iVar1 + 0x5160;
  } while (iVar1 < param_1 + 0xa2c0);
  DAT_8009c8a8 = _DAT_800ff430;
  DAT_8009c8ac = DAT_800ff434;
  DAT_8009c8b0 = DAT_800ff438;
  DAT_8009c8b4 = DAT_800ff43c;
  DAT_8009c8b8 = DAT_800ff440;
  FUN_80086d50();
  FUN_800856c8();
  FUN_80085538(0,0);
  FUN_80087858(300);
  FUN_8008b738(1);
  FUN_8003cde4();
  FUN_80013600();
  FUN_8008f738(0x56);
  return;
}

