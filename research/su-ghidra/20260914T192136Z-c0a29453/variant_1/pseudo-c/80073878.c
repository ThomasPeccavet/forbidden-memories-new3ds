/* Analysis pseudo-C, not buildable source. */

void FUN_80073878(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar1 = FUN_80070bb8();
  iVar3 = 0;
  puVar2 = &DAT_800f6f70;
  while( true ) {
    if ((uint)*(ushort *)(puVar2 + 0x3e) == *(uint *)(&DAT_800f6f20 + iVar1 * 4)) {
      return;
    }
    if (*(ushort *)(puVar2 + 0x3e) == 0) break;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 2;
    if (0x1f < iVar3) {
      return;
    }
  }
  *(short *)(puVar2 + 0x3e) = (short)*(uint *)(&DAT_800f6f20 + iVar1 * 4);
  return;
}

