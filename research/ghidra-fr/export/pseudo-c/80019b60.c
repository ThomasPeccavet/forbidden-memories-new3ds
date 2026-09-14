/* Analysis pseudo-C, not buildable source. */

void FUN_80019b60(int param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = FUN_80042ec8();
  if (iVar1 == 0) {
    *(undefined2 *)(param_1 + 0x2e) = 0x40;
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
    if (*(char *)(param_1 + 0x21) != '\0') {
      *(undefined2 *)(param_1 + 0x2e) = 0xc0;
    }
  }
  bVar2 = *(char *)(param_1 + 0x21) + 8;
  *(byte *)(param_1 + 0x21) = bVar2;
  if ((*(byte *)(param_1 + 0x6c) & 0x40) == 0) {
    if (*(short *)(param_1 + 0x2e) <= (short)(ushort)*(byte *)(param_1 + 0x21)) {
      *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x40;
      *(undefined1 *)(param_1 + 0x21) = 0xc0;
      *(undefined1 *)(param_1 + 0x67) = 0;
    }
  }
  else if (-1 < (int)((uint)bVar2 << 0x18)) {
    *(undefined1 *)(param_1 + 0x21) = 0;
    (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] =
         (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] & 0xdfff;
    if (*(char *)(param_1 + 0x22) == '\0' && *(char *)(param_1 + 0x20) == '\0') {
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfffb;
    }
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  return;
}

