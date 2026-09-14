/* Analysis pseudo-C, not buildable source. */

int FUN_80017f94(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_80017e94();
  if (*(char *)(DAT_8009c500 + 0x1f) != '\0') {
    *(ushort *)(param_1 + 0x16) = *(ushort *)(param_1 + 0x16) | 0x2000;
    *(char *)(iVar1 + 0x67) = *(char *)(*(int *)(param_1 + 4) + 4) + '\x01';
    if (*(char *)(DAT_8009c500 + 0x1f) < '\0') {
      *(undefined1 *)(iVar1 + 0x67) = 0xff;
    }
  }
  return iVar1;
}

