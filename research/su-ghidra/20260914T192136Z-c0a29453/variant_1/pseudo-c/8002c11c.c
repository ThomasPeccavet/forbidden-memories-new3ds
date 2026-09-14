/* Analysis pseudo-C, not buildable source. */

void FUN_8002c11c(void)

{
  int iVar1;
  char *pcVar2;
  ushort *puVar3;
  
  pcVar2 = &DAT_801d0250;
  iVar1 = 0;
  do {
    if (*pcVar2 != '\0') {
      FUN_8002ceb8(iVar1 + 0x121);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
  } while (iVar1 < 0x2d2);
  puVar3 = &DAT_801d0200;
  iVar1 = 0;
  do {
    if (*puVar3 != 0) {
      FUN_8002ceb8(*puVar3 + 0x120);
    }
    iVar1 = iVar1 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar1 < 0x28);
  return;
}

