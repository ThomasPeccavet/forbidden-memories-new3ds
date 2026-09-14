/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800456c4(ushort param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  short sVar5;
  undefined1 local_48 [2];
  short local_46;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 *local_3c;
  
  iVar1 = DAT_8009c7e0;
  if ((*(byte *)(DAT_8009c7e0 + 0x4a) & 0x80) != 0) {
    if (((*(byte *)(DAT_8009c7e0 + 0x4a) & 0x40) == 0) && (0x9fff < param_1)) {
      return 0;
    }
    if ((param_1 & 0x8000) != 0) {
      *(ushort *)(DAT_8009c7e0 + 0x534) = param_1;
      if ((param_1 & 0xf000) == 0x8000) {
        sVar5 = param_1 + 0x8000;
        puVar2 = *(undefined4 **)(iVar1 + 0x51c);
        uVar4 = 0x50;
      }
      else {
        sVar5 = param_1 + 0x6000;
        if ((param_1 & 0xf000) == 0x9000) {
          sVar5 = param_1 + 0x7000;
          puVar2 = *(undefined4 **)(iVar1 + 0x518);
          uVar4 = 0x60;
        }
        else {
          uVar4 = 0x70;
          puVar2 = *(undefined4 **)(DAT_8009c7e0 + 0x520);
        }
      }
      uVar3 = *puVar2;
      FUN_800469ac();
      local_48[0] = 0x24;
      local_46 = sVar5;
      local_44 = uVar3;
      local_40 = uVar4;
      local_3c = puVar2 + 2;
      FUN_800460a4(local_48);
      FUN_8004525c();
      *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) & 0xfffb | 1;
      return 1;
    }
  }
  return 0;
}

