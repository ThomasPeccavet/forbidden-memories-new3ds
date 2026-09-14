/* Analysis pseudo-C, not buildable source. */

void FUN_80017d44(int param_1)

{
  if ((((*(uint *)(&DAT_801a7aec + (uint)*(byte *)(param_1 + 0x6a) * 0xe) & 0xa0000000) ==
        0xa0000000) && (*(char *)(DAT_8009c500 + 0x1f) != '\0')) &&
     (*(char *)(param_1 + 0x67) =
           *(char *)((&DAT_801a7adc)[(uint)*(byte *)(param_1 + 0x6a) * 7] + 4) + '\x01',
     *(char *)(DAT_8009c500 + 0x1f) < '\0')) {
    *(undefined1 *)(param_1 + 0x67) = 0xff;
  }
  return;
}

