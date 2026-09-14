/* Analysis pseudo-C, not buildable source. */

void FUN_80025bd8(int param_1)

{
  byte bVar1;
  
  bVar1 = *(char *)(param_1 + 0x22) + 8;
  *(byte *)(param_1 + 0x22) = bVar1;
  if (((*(byte *)(param_1 + 0x6c) & 0x80) == 0) && (0x27 < bVar1)) {
    *(byte *)(param_1 + 0x6c) = *(byte *)(param_1 + 0x6c) | 0x80;
    (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] =
         (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] & 0xdfff;
    *(undefined1 *)(param_1 + 0x67) = 0;
  }
  if (*(byte *)(param_1 + 0x22) < 0x40) {
    *(undefined1 *)(param_1 + 0x22) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] =
         (&DAT_801a7aee)[(uint)*(byte *)(param_1 + 0x6a) * 0xe] & 0xcbff;
    FUN_80018010(param_1);
  }
  return;
}

