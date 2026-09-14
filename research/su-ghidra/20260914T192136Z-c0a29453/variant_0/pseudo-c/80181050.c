/* Analysis pseudo-C, not buildable source. */

void FUN_80181050(undefined2 *param_1,undefined2 *param_2,char *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_80040350();
  DAT_801847cc = FUN_800403d0(uVar1,2);
  if (DAT_801847cc != 0) {
    FUN_80040800(DAT_801847cc,0,0,0,4,0xb,0xc,0x208);
    iVar2 = DAT_801847cc;
    *(ushort *)(DAT_801847cc + 8) = *(ushort *)(DAT_801847cc + 8) | 0x28;
    FUN_80042c1c(iVar2,0xfffffffd);
  }
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,4);
  FUN_80042b0c(iVar2,0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x60000000;
  FUN_80042c1c(iVar2,0xfffffffe);
  *(undefined4 *)(iVar2 + 0x28) = 0xe00000;
  *(undefined4 *)(iVar2 + 0x30) = 0xe00140;
  *(undefined4 *)(iVar2 + 0x38) = 0x1000000;
  *(undefined4 *)(iVar2 + 0x40) = 0x1000140;
  *(undefined4 *)(iVar2 + 0x3c) = 0x808080;
  *(undefined4 *)(iVar2 + 0x44) = 0x808080;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,4);
  FUN_80042b0c(iVar2,0);
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x60000000;
  FUN_80042c1c(iVar2,0xfffffffe);
  *(undefined4 *)(iVar2 + 0x30) = 0x140;
  *(undefined4 *)(iVar2 + 0x28) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0x100000;
  *(undefined4 *)(iVar2 + 0x40) = 0x100140;
  *(undefined4 *)(iVar2 + 0x2c) = 0x808080;
  *(undefined4 *)(iVar2 + 0x34) = 0x808080;
  uVar1 = FUN_80040350();
  DAT_801847d0 = FUN_800403d0(uVar1,2);
  if (DAT_801847d0 != 0) {
    FUN_80042bd8(DAT_801847d0,0,10,6,0,0,0xe,5,&DAT_801af800);
    iVar2 = DAT_801847d0;
    *(ushort *)(DAT_801847d0 + 8) = *(ushort *)(DAT_801847d0 + 8) | 0x28;
    FUN_80042c1c(iVar2,0xffffffff);
  }
  uVar1 = FUN_80040350();
  DAT_801847dc = FUN_800403d0(uVar1,2);
  if (DAT_801847dc != 0) {
    FUN_80040800(DAT_801847dc,0,0,3,4,0,0xb,0x20c);
    *(ushort *)(DAT_801847dc + 8) = *(ushort *)(DAT_801847dc + 8) | 0x28;
    FUN_80042c1c(DAT_801847dc,1);
  }
  uVar1 = FUN_80040350();
  DAT_801847e0 = FUN_800403d0(uVar1,2);
  if (DAT_801847e0 != 0) {
    FUN_80040800(DAT_801847e0,0,0,3,4,0,0xb,0x20c);
    *(ushort *)(DAT_801847e0 + 8) = *(ushort *)(DAT_801847e0 + 8) | 0x28;
    FUN_80042c1c(DAT_801847e0,1);
  }
  uVar1 = FUN_80040350();
  DAT_801847e4 = FUN_800403d0(uVar1,2);
  if (DAT_801847e4 != 0) {
    FUN_80040800(DAT_801847e4,0,0,3,4,0,0xb,0x20c);
    *(ushort *)(DAT_801847e4 + 8) = *(ushort *)(DAT_801847e4 + 8) | 0x28;
    FUN_80042c1c(DAT_801847e4,1);
  }
  DAT_80184804 = param_3;
  DAT_801847e9 = 2;
  DAT_801847e8 = 2;
  DAT_801847f0 = param_1;
  DAT_801847fc = param_2;
  DAT_801847ea = *param_3 == '\0';
  DAT_801847ee = *param_1;
  DAT_801847ec = *param_1;
  DAT_8009c898 = FUN_8018187c;
  DAT_801847fa = *param_2;
  DAT_801847f8 = *param_2;
  return;
}

