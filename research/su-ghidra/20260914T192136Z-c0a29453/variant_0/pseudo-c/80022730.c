/* Analysis pseudo-C, not buildable source. */

void FUN_80022730(int param_1)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined2 uVar5;
  
  uVar3 = (uint)*(byte *)(param_1 + 0x6a);
  iVar4 = FUN_80042ec8();
  if (iVar4 == 0) {
    uVar5 = 0;
    if ((((&DAT_801a7aee)[uVar3 * 0xe] & 0x1000) == 0) &&
       (uVar5 = 1, ((&DAT_801a7aee)[uVar3 * 0xe] & 0x800) != 0)) {
      uVar5 = 2;
    }
    *(undefined2 *)(param_1 + 0x2e) = uVar5;
  }
  sVar2 = *(short *)(param_1 + 0x2e);
  if (sVar2 == 1) {
    if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined2 *)(param_1 + 0x28) = 0x1000;
      *(undefined2 *)(param_1 + 0x2a) = 0x80;
      *(undefined4 *)(param_1 + 0x20) = 0;
      *(undefined2 *)(param_1 + 0x60) = 4;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x20) == 0) {
      if (DAT_8009c504 == '\0') {
        sVar2 = *(short *)(param_1 + 0x2a) + *(short *)(param_1 + 0x28);
      }
      else {
        sVar2 = *(short *)(param_1 + 0x2a) - *(short *)(param_1 + 0x28);
      }
      *(short *)(param_1 + 0x2a) = sVar2;
      sVar2 = *(short *)(param_1 + 0x60);
      *(short *)(param_1 + 0x60) = sVar2 + -1;
      *(char *)(param_1 + 0x22) = (char)((ushort)*(undefined2 *)(param_1 + 0x2a) >> 8);
      if (sVar2 != 1) {
        return;
      }
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x20;
      (&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] | 0x400;
      *(undefined4 *)(param_1 + 0x20) = 0x4000;
      *(undefined2 *)(param_1 + 0x2a) = 0x4080;
      uVar1 = *(ushort *)(param_1 + 8);
LAB_80022a50:
      *(undefined2 *)(param_1 + 0x60) = 4;
      *(ushort *)(param_1 + 8) = uVar1 | 4;
      return;
    }
    iVar4 = (uint)*(ushort *)(param_1 + 0x2a) - (uint)*(ushort *)(param_1 + 0x28);
    sVar2 = *(short *)(param_1 + 0x60);
    *(short *)(param_1 + 0x2a) = (short)iVar4;
    *(char *)(param_1 + 0x21) = (char)((uint)iVar4 >> 8);
    *(short *)(param_1 + 0x60) = sVar2 + -1;
    if (sVar2 != 1) {
      return;
    }
    *(undefined1 *)(param_1 + 0x21) = 0;
  }
  else if (sVar2 < 2) {
    if (sVar2 != 0) {
      return;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined2 *)(param_1 + 0x60) = 8;
      (&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] | 0x400;
      *(undefined4 *)(param_1 + 0x20) = 0x8000;
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
      if (((&DAT_801a7aee)[uVar3 * 0xe] & 0x800) != 0) {
        *(undefined1 *)(param_1 + 0x22) = 0xc0;
      }
    }
    sVar2 = *(short *)(param_1 + 0x60);
    *(short *)(param_1 + 0x60) = sVar2 + -1;
    if (sVar2 == 1) {
      return;
    }
  }
  else {
    if (sVar2 != 2) {
      return;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined4 *)(param_1 + 0x20) = 0xc000;
      *(undefined2 *)(param_1 + 0x28) = 0x1000;
      *(undefined2 *)(param_1 + 0x2a) = 0x80;
      *(undefined2 *)(param_1 + 0x60) = 4;
    }
    if ((*(byte *)(param_1 + 0x6c) & 0x20) == 0) {
      if (DAT_8009c504 == '\0') {
        sVar2 = *(short *)(param_1 + 0x2a) + *(short *)(param_1 + 0x28);
      }
      else {
        sVar2 = *(short *)(param_1 + 0x2a) - *(short *)(param_1 + 0x28);
      }
      *(short *)(param_1 + 0x2a) = sVar2;
      sVar2 = *(short *)(param_1 + 0x60);
      *(short *)(param_1 + 0x60) = sVar2 + -1;
      *(char *)(param_1 + 0x22) = (char)((ushort)*(undefined2 *)(param_1 + 0x2a) >> 8);
      if (sVar2 != 1) {
        return;
      }
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x20;
      (&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] | 0x400;
      *(undefined2 *)(param_1 + 0x2a) = 0xc080;
      uVar1 = *(ushort *)(param_1 + 8);
      *(undefined4 *)(param_1 + 0x20) = 0xc000c0;
      goto LAB_80022a50;
    }
    iVar4 = (uint)*(ushort *)(param_1 + 0x2a) + (uint)*(ushort *)(param_1 + 0x28);
    sVar2 = *(short *)(param_1 + 0x60);
    *(short *)(param_1 + 0x2a) = (short)iVar4;
    *(char *)(param_1 + 0x20) = (char)((uint)iVar4 >> 8);
    *(short *)(param_1 + 0x60) = sVar2 + -1;
    if (sVar2 != 1) {
      return;
    }
    *(undefined1 *)(param_1 + 0x20) = 0;
  }
  *(undefined1 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  FUN_80017dcc();
  return;
}

