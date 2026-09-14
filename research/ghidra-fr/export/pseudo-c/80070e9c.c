/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80070e9c(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_800f6f70;
  do {
    iVar2 = iVar2 + 1;
    if ((int)*(short *)(&DAT_801ab000 + param_1 * 0xc) == (uint)*(ushort *)(puVar1 + 0x3e)) {
      return 1;
    }
    puVar1 = puVar1 + 2;
  } while (iVar2 < 0x20);
  return 0;
}

