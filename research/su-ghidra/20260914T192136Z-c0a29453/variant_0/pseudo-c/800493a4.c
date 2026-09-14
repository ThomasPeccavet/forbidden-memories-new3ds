/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800493a4(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  undefined2 local_16;
  
  FUN_80076d28(1);
  FUN_80076158(1);
  local_20 = 7;
  local_1c = 2;
  local_18 = 0x7fff;
  local_16 = 0x7fff;
  FUN_80076378(&local_20);
  iVar1 = DAT_8009c7e0;
  *(undefined2 *)(DAT_8009c7e0 + 0x1586) = 0;
  *(undefined2 *)(iVar1 + 0x1588) = 0;
  *(undefined1 *)(iVar1 + 0x158a) = 0;
  iVar1 = DAT_8009c7e0;
  *(undefined2 *)(DAT_8009c7e0 + 0x1580) = 0xff;
  *(undefined1 *)(iVar1 + 0x1584) = 0xff;
  iVar2 = DAT_8009c7e0;
  *(undefined2 *)(iVar1 + 0x1582) = 0;
  *(undefined1 **)(iVar2 + 0x1564) = &DAT_801ea800;
  *(undefined4 *)(iVar2 + 0x1560) = 0x801e2000;
  *(undefined2 *)(iVar2 + 0x1578) = 0xffff;
  *(undefined2 *)(iVar2 + 0x157a) = 0xffff;
  *(undefined2 *)(iVar2 + 0x157c) = 0xffff;
  *(undefined2 *)(iVar2 + 0x157e) = 0xffff;
  _DAT_801ea800 = 0xffff;
  *(undefined2 *)(*(int *)(iVar2 + 0x1564) + 2) = 0;
  *(undefined4 *)(*(int *)(iVar2 + 0x1564) + 4) = 0;
  *(undefined4 *)(*(int *)(iVar2 + 0x1564) + 8) = 0;
  *(undefined4 *)(*(int *)(iVar2 + 0x1564) + 0xc) = 0x40000;
  FUN_80049a24(2);
  FUN_80049a90(0x14);
  FUN_800499d4();
  return;
}

