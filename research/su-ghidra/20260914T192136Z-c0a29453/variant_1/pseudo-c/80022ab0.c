/* Analysis pseudo-C, not buildable source. */

void FUN_80022ab0(int param_1)

{
  bool bVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined2 uVar7;
  
  uVar4 = (uint)*(byte *)(param_1 + 0x6a);
  iVar5 = FUN_80042ec8();
  if (iVar5 == 0) {
    uVar7 = 0;
    if ((((&DAT_801a7aee)[uVar4 * 0xe] & 0x1000) == 0) &&
       (uVar7 = 1, ((&DAT_801a7aee)[uVar4 * 0xe] & 0x800) != 0)) {
      uVar7 = 2;
    }
    *(undefined2 *)(param_1 + 0x2e) = uVar7;
  }
  sVar3 = *(short *)(param_1 + 0x2e);
  if (sVar3 == 1) {
    if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined2 *)(param_1 + 0x28) = 0x1000;
      *(undefined2 *)(param_1 + 0x2a) = 0x80;
      *(undefined4 *)(param_1 + 0x20) = 0;
      *(undefined2 *)(param_1 + 0x60) = 4;
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x20) != 0) {
      if (DAT_8009c504 == '\0') {
        sVar3 = *(short *)(param_1 + 0x2a) - *(short *)(param_1 + 0x28);
      }
      else {
        sVar3 = *(short *)(param_1 + 0x2a) + *(short *)(param_1 + 0x28);
      }
      *(short *)(param_1 + 0x2a) = sVar3;
      sVar3 = *(short *)(param_1 + 0x60);
      *(short *)(param_1 + 0x60) = sVar3 + -1;
      *(char *)(param_1 + 0x22) = (char)((ushort)*(undefined2 *)(param_1 + 0x2a) >> 8);
      if (sVar3 != 1) {
        return;
      }
      *(undefined1 *)(param_1 + 0x22) = 0;
      goto LAB_80022bd0;
    }
    iVar5 = (uint)*(ushort *)(param_1 + 0x2a) + (uint)*(ushort *)(param_1 + 0x28);
    sVar3 = *(short *)(param_1 + 0x60);
    *(short *)(param_1 + 0x2a) = (short)iVar5;
    *(char *)(param_1 + 0x21) = (char)((uint)iVar5 >> 8);
    *(short *)(param_1 + 0x60) = sVar3 + -1;
    if (sVar3 != 1) {
      return;
    }
    *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x20;
    bVar1 = DAT_8009c504 != '\0';
    (&DAT_801a7aee)[uVar4 * 0xe] = (&DAT_801a7aee)[uVar4 * 0xe] & 0xfbff;
    if (bVar1) {
      *(undefined4 *)(param_1 + 0x20) = 0xc00000;
      uVar7 = 0xc080;
      goto LAB_80022dd0;
    }
    uVar6 = 0x400000;
  }
  else {
    if (sVar3 < 2) {
      if (sVar3 != 0) {
        return;
      }
      if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
        *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
        *(undefined2 *)(param_1 + 0x60) = 8;
      }
      uVar2 = *(short *)(param_1 + 0x60) - 1;
      *(ushort *)(param_1 + 0x60) = uVar2;
      if (0 < (int)((uint)uVar2 << 0x10)) {
        return;
      }
      (&DAT_801a7aee)[uVar4 * 0xe] = (&DAT_801a7aee)[uVar4 * 0xe] & 0xfbff;
      *(undefined1 *)(param_1 + 0x22) = 0x80;
      *(undefined1 *)(param_1 + 0x20) = 0;
      *(undefined1 *)(param_1 + 0x21) = 0;
      *(undefined4 *)(param_1 + 0x20) = 0x800000;
      if (((&DAT_801a7aee)[uVar4 * 0xe] & 0x800) != 0) {
        *(undefined1 *)(param_1 + 0x21) = 0xc0;
      }
LAB_80022bd0:
      *(undefined1 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0x24) = 0;
      FUN_80018010();
      return;
    }
    if (sVar3 != 2) {
      return;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined4 *)(param_1 + 0x20) = 0xc00000;
      *(undefined2 *)(param_1 + 0x28) = 0x1000;
      *(undefined2 *)(param_1 + 0x2a) = 0x80;
      *(undefined2 *)(param_1 + 0x60) = 4;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x20) != 0) {
      if (DAT_8009c504 == '\0') {
        sVar3 = *(short *)(param_1 + 0x2a) - *(short *)(param_1 + 0x28);
      }
      else {
        sVar3 = *(short *)(param_1 + 0x2a) + *(short *)(param_1 + 0x28);
      }
      *(short *)(param_1 + 0x2a) = sVar3;
      sVar3 = *(short *)(param_1 + 0x60);
      *(short *)(param_1 + 0x60) = sVar3 + -1;
      *(char *)(param_1 + 0x22) = (char)((ushort)*(undefined2 *)(param_1 + 0x2a) >> 8);
      if (sVar3 != 1) {
        return;
      }
      *(undefined1 *)(param_1 + 0x20) = 0;
      goto LAB_80022bd0;
    }
    iVar5 = (uint)*(ushort *)(param_1 + 0x2a) - (uint)*(ushort *)(param_1 + 0x28);
    sVar3 = *(short *)(param_1 + 0x60);
    *(short *)(param_1 + 0x2a) = (short)iVar5;
    *(char *)(param_1 + 0x20) = (char)((uint)iVar5 >> 8);
    *(short *)(param_1 + 0x60) = sVar3 + -1;
    if (sVar3 != 1) {
      return;
    }
    *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x20;
    bVar1 = DAT_8009c504 != '\0';
    (&DAT_801a7aee)[uVar4 * 0xe] = (&DAT_801a7aee)[uVar4 * 0xe] & 0xfbff;
    if (bVar1) {
      *(undefined4 *)(param_1 + 0x20) = 0xc0c000;
      uVar7 = 0xc080;
      goto LAB_80022dd0;
    }
    uVar6 = 0x40c000;
  }
  *(undefined4 *)(param_1 + 0x20) = uVar6;
  uVar7 = 0x4080;
LAB_80022dd0:
  *(undefined2 *)(param_1 + 0x2a) = uVar7;
  *(undefined2 *)(param_1 + 0x60) = 4;
  return;
}

