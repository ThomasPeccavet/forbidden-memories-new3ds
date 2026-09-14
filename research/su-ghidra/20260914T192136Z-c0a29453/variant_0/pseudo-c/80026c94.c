/* Analysis pseudo-C, not buildable source. */

int FUN_80026c94(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  param_1 = (uint)DAT_8009c504 * 0xf + param_1;
  puVar1 = &DAT_801a7ad8 + param_1 * 7;
  do {
    if ((*(ushort *)((int)puVar1 + 0x16) & 0x8000) == 0) {
      return param_1 + iVar2;
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 7;
  } while (iVar2 < 5);
  return -1;
}

