/* Analysis pseudo-C, not buildable source. */

void FUN_8001d1a0(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_80042ec8();
  if (iVar2 == 0) {
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
    if (*(char *)(param_1 + 0x22) == '\0') {
      *(undefined2 *)(param_1 + 0x28) = 0xfff8;
      *(undefined2 *)(param_1 + 0x2a) = 0xc0;
    }
    else {
      *(undefined2 *)(param_1 + 0x28) = 8;
      *(undefined2 *)(param_1 + 0x2a) = 0;
    }
  }
  bVar1 = *(char *)(param_1 + 0x22) + *(char *)(param_1 + 0x28);
  *(byte *)(param_1 + 0x22) = bVar1;
  if (bVar1 < 0xc0) {
    uVar3 = (uint)*(byte *)(param_1 + 0x6a);
    (&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] | 0x800;
    *(char *)(param_1 + 0x22) = *(char *)(param_1 + 0x2a);
    if ((*(char *)(param_1 + 0x2a) == '\0') &&
       ((&DAT_801a7aee)[uVar3 * 0xe] = (&DAT_801a7aee)[uVar3 * 0xe] & 0xf7ff,
       *(char *)(param_1 + 0x21) == '\0')) {
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfffb;
    }
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  return;
}

