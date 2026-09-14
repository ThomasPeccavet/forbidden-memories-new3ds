/* Analysis pseudo-C, not buildable source. */

void FUN_8001798c(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  uint uVar5;
  
  FUN_80047acc();
  FUN_80047f60(1);
  FUN_80012c88(4);
  FUN_80013700();
  FUN_80014d38(0,0,(uint)DAT_8009c6f9 * 0xf0 + 0x1b88,0xf0,FUN_800170c4,0,0);
  FUN_80013700();
  DAT_8009c561 = 0xff;
  DAT_8009c564 = 0xb;
  DAT_8009c580 = 0;
  DAT_8009c57e = 0;
  DAT_8009c5c0 = 0;
  DAT_8009c4cc = 0;
  DAT_8009c550 = 0;
  DAT_8009c582 = 0;
  DAT_8009c585 = 0;
  if (DAT_8009c6fc != '\x01') {
    if (-1 < DAT_8009c6f3) {
      FUN_80014d38(0,0,DAT_8009c6f3 * 3 + 0x2218,3,0,0,&DAT_801781d8);
    }
    DAT_8009c504 = 0;
    DAT_8009c564 = 1;
    FUN_80017730();
    FUN_800176ac();
    FUN_80017544();
    DAT_8009c582 = DAT_8009c582 | 0x1000;
  }
  DAT_8009c500 = &DAT_800eb278 + (uint)DAT_8009c504 * 0x20;
  FUN_80017860();
  DAT_800f11e2 = (ushort)DAT_8009c504 * 0x800 + 0x400;
  FUN_80013448();
  FUN_80017674();
  FUN_8002c76c();
  FUN_8002970c(0);
  DAT_800eb498 = 0;
  DAT_800eb49a = 0x100;
  DAT_800eb49c = 0x280;
  DAT_800eb49e = 0xdf;
  FUN_8002970c(1);
  DAT_800eb4d8 = 0x40;
  DAT_800eb4da = 0x100;
  DAT_800eb4dc = 0x280;
  DAT_800eb4de = 0xde;
  FUN_80035b68(0);
  FUN_80017500();
  FUN_80013700();
  DAT_8009c51c = &DAT_800919e0 + (uint)DAT_8009c504 * 0x14;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,0xc,0x18,4,2,DAT_8009c6f9,0xb,0x2dc);
  FUN_80042c48(iVar2);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 8;
  uVar5 = (uint)DAT_8009c6f3;
  DAT_8009c4e8 = iVar2;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,0x118,0x20,4,uVar5 >> 0x1f,0,0xb,0x2ec);
  FUN_80042c48(iVar2);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 8;
  if (DAT_8009c504 != 0) {
    *(short *)(iVar2 + 0x40) = *(short *)(iVar2 + 0x40) + 0x10;
  }
  DAT_8009c55c = iVar2;
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,6);
  FUN_80042c48(iVar2);
  FUN_80042c1c(iVar2,1);
  *(code **)(iVar2 + 0x4c) = FUN_80016d8c;
  *(int *)(iVar2 + 0x50) = DAT_8009c55c;
  DAT_8009c8a4 = FUN_80016418;
  if (DAT_8009c6fc == '\x01') {
    DAT_8009c8a4 = FUN_80016418;
    return;
  }
  DAT_8009c4fc = (undefined *)0x0;
  DAT_8009c4f8 = (undefined2 *)0x0;
  puVar3 = (undefined2 *)0x0;
  if (DAT_8009c6f2 < '\0') {
    if (DAT_8009c6f3 < '\0') {
      puVar3 = (undefined2 *)&DAT_801d1200;
      DAT_8009c4f8 = (undefined2 *)&DAT_801d1200;
      DAT_8009c4fc = &DAT_801d2200;
      puVar4 = (undefined2 *)&DAT_801d2200;
      goto LAB_80017d24;
    }
    puVar3 = &DAT_801d0200;
    DAT_8009c4f8 = &DAT_801d0200;
    puVar4 = (undefined2 *)0x0;
    if (DAT_8009c6f3 < '\'') goto LAB_80017d24;
  }
  puVar4 = puVar3;
LAB_80017d24:
  FUN_8002465c(puVar3,puVar4);
  return;
}

