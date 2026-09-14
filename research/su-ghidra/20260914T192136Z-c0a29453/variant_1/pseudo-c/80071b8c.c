/* Analysis pseudo-C, not buildable source. */

void FUN_80071b8c(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_80070bb8();
  puVar2 = &DAT_800f6f70;
  iVar3 = 0;
  do {
    if ((byte)puVar2[0x38] - 1 < 10) {
      *(uint *)(&DAT_800f6f20 + iVar1 * 4) = (uint)(byte)puVar2[0x38];
      return;
    }
    iVar4 = iVar3 + 1;
    puVar2 = &DAT_800f6f71 + iVar3;
    iVar3 = iVar4;
  } while (iVar4 < 5);
  *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  return;
}

