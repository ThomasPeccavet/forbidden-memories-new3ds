/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80046ec4(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  switch(DAT_8009c7e0[0xf]) {
  case 0:
    if ((*(byte *)((int)DAT_8009c7e0 + 0x4a) & 1) == 0) {
      DAT_8009c7e0[0xf] = DAT_8009c7e0[0xf] + 6;
      return;
    }
    puVar4 = &DAT_801e6800;
    uVar5 = 0;
    iVar3 = 0x800;
    uVar6 = 0x10;
    goto LAB_80047120;
  case 1:
    uVar1 = FUN_800474cc();
    uVar5 = _DAT_801e6804;
    puVar2 = DAT_8009c7e0;
    if ((uVar1 & 7) != 0) {
      return;
    }
    *DAT_8009c7e0 = _DAT_801e6800;
    puVar2[1] = uVar5;
    break;
  case 2:
    puVar4 = (undefined1 *)0x801e2800;
    uVar5 = 1;
    uVar6 = 0x10;
    iVar3 = (uint)*(ushort *)((int)DAT_8009c7e0 + 2) << 3;
    goto LAB_80047120;
  case 3:
    uVar1 = FUN_800474cc();
    if ((uVar1 & 7) != 0) {
      return;
    }
    FUN_80047910();
    puVar2 = DAT_8009c7e0;
    break;
  case 4:
    FUN_80047c18(0);
    puVar2 = DAT_8009c7e0;
    break;
  case 5:
    uVar1 = FUN_800474cc();
    puVar2 = DAT_8009c7e0;
    if ((uVar1 & 7) != 0) {
      return;
    }
    break;
  case 6:
    if ((*(byte *)((int)DAT_8009c7e0 + 0x4a) & 2) == 0) {
      DAT_8009c7e0[0xf] = DAT_8009c7e0[0xf] + 2;
      return;
    }
    puVar4 = (undefined1 *)0x801e2000;
    uVar5 = 0;
    iVar3 = 0x800;
    uVar6 = 0x20;
    goto LAB_80047120;
  case 7:
    uVar1 = FUN_800474cc();
    if ((uVar1 & 7) != 0) {
      return;
    }
    puVar2 = DAT_8009c7e0;
    if ((((DAT_801e27f8 == 'V') && (DAT_801e27f9 == 'o')) &&
        ((DAT_801e27fa == 'l' &&
         (((DAT_801e27fb == 'I' && (DAT_801e27fc == 'n')) && (DAT_801e27fd == 'f')))))) &&
       (DAT_801e27fe == 'o')) {
      *(undefined1 *)((int)DAT_8009c7e0 + 0x164a) = DAT_801e27ff;
      *(ushort *)(DAT_8009c7e0 + 0x11) = (ushort)*(byte *)((int)DAT_8009c7e0 + 0x164a);
      puVar2 = DAT_8009c7e0;
    }
    break;
  case 8:
    if ((*(byte *)((int)DAT_8009c7e0 + 0x4a) & 0x80) == 0) {
      DAT_8009c7e0[0xf] = 999;
      return;
    }
    puVar4 = (undefined1 *)0x801e8800;
    uVar5 = 0;
    iVar3 = 0x2000;
    uVar6 = 0x40;
LAB_80047120:
    FUN_80047540(puVar4,uVar5,iVar3,uVar6);
    puVar2 = DAT_8009c7e0;
    break;
  case 9:
    uVar1 = FUN_800474cc();
    if ((uVar1 & 7) != 0) {
      return;
    }
    if ((((DAT_801e8ff8 == 'V') && (DAT_801e8ff9 == 'o')) && (DAT_801e8ffa == 'l')) &&
       (((DAT_801e8ffb == 'I' && (DAT_801e8ffc == 'n')) &&
        ((DAT_801e8ffd == 'f' && (DAT_801e8ffe == 'o')))))) {
      *(undefined1 *)((int)DAT_8009c7e0 + 0x1649) = DAT_801e8fff;
      *(ushort *)((int)DAT_8009c7e0 + 0x42) = (ushort)*(byte *)((int)DAT_8009c7e0 + 0x1649);
    }
    puVar2 = DAT_8009c7e0;
    iVar3 = DAT_8009c7e0[0xf];
    DAT_8009c7e0[0x146] = 0x801e8800;
    puVar2[0x147] = 0x801e9000;
    puVar2[0x148] = 0x801ea000;
    puVar2[0xf] = iVar3 + 1;
    return;
  default:
    uVar1 = FUN_800474cc();
    if ((uVar1 & 7) != 0) {
      return;
    }
    *(ushort *)(DAT_8009c7e0 + 0x10) = *(ushort *)(DAT_8009c7e0 + 0x10) & 0xfff7;
    return;
  }
  puVar2[0xf] = puVar2[0xf] + 1;
  return;
}

