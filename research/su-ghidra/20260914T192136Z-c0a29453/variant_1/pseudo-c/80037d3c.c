/* Analysis pseudo-C, not buildable source. */

void FUN_80037d3c(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  
  puVar4 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar4;
  bVar1 = *pbVar2;
  *puVar4 = pbVar2 + 1;
  if ((bVar1 & 0x10) != 0) {
    *(undefined1 *)(param_1 + 0x54) = DAT_8009c6e1;
    return;
  }
  if ((bVar1 & 0x20) == 0) {
    bVar3 = bVar1 & 0xf;
    if ((bVar1 & 0x40) == 0) {
      uVar7 = 0;
      if (bVar3 == 1) {
        uVar7 = (int)(&DAT_801d4244)[DAT_8009c6b8 + -1] >> 0x16;
LAB_80037e68:
        uVar7 = (uVar7 & 0xf) + 0x17;
      }
      else if (bVar3 < 2) {
        if ((bVar1 & 0xf) == 0) {
          uVar7 = (int)(&DAT_801d4244)[DAT_8009c6b8 + -1] >> 0x1a & 0x1f;
        }
      }
      else {
        if (bVar3 == 2) {
          uVar7 = (int)(&DAT_801d4244)[DAT_8009c6b8 + -1] >> 0x12;
          goto LAB_80037e68;
        }
        if (bVar3 == 3) {
          uVar7 = (int)(&DAT_801d4244)[DAT_8009c6b8 + -1] >> 0x1a & 0x1fU | 0x80;
        }
      }
      if ((bVar1 & 0x80) == 0) {
        *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) | 0x100;
        FUN_80036c64(param_1);
        *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) & 0xfeff;
        *(short *)(param_1 + 0x38) = *(short *)(param_1 + 0x38) + 0x10;
        return;
      }
      iVar6 = uVar7 + 0x8300;
    }
    else {
      iVar6 = DAT_8009c6b8 + 0x100;
    }
  }
  else {
    iVar6 = DAT_8009c6b8 + 0x8000;
  }
  *(char *)(param_1 + 0x58) = *(char *)(param_1 + 0x58) + '\x01';
  if (iVar6 < 0x8000) {
    if (0x4ff < iVar6) {
      puVar5 = &DAT_801c0000 + *(ushort *)(&DAT_801b0004 + (iVar6 + -0x100) * 2);
      goto LAB_80037f40;
    }
    puVar5 = &DAT_801b0004;
    iVar6 = iVar6 << 1;
  }
  else {
    puVar5 = &DAT_801d5804;
    iVar6 = (iVar6 + -0x8000) * 2;
  }
  puVar5 = (undefined *)(((uint)puVar5 & 0xffff0000) + (uint)*(ushort *)(puVar5 + iVar6));
LAB_80037f40:
  *(undefined **)(param_1 + *(char *)(param_1 + 0x58) * 4) = puVar5;
  return;
}

