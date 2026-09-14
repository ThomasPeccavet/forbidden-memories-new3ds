/* Analysis pseudo-C, not buildable source. */

void FUN_80073910(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  puVar2 = &DAT_800f6f70;
  iVar3 = 0;
  while( true ) {
    if ((uint)(byte)puVar2[0x7e] == *(int *)(&DAT_800f6f20 + iVar1 * 4) + 1U) {
      return;
    }
    if ((byte)puVar2[0x7e] == 0) break;
    iVar4 = iVar3 + 1;
    puVar2 = &DAT_800f6f71 + iVar3;
    iVar3 = iVar4;
    if (0x18 < iVar4) {
      return;
    }
  }
  puVar2[0x7e] = (char)(*(int *)(&DAT_800f6f20 + iVar1 * 4) + 1U);
  return;
}

