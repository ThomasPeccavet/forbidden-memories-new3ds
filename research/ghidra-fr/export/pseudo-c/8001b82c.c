/* Analysis pseudo-C, not buildable source. */

void FUN_8001b82c(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_800eb2b8;
  do {
    if (*(char *)((int)piVar1 + 9) == '\0') {
      *(undefined4 *)(*piVar1 + 0xc) = 0x404040;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 3;
  } while (iVar2 < 5);
  if (*(char *)(param_1 + 0x15) == '\0') {
    *(undefined4 *)((&DAT_800eb2b8)[*(char *)(param_1 + 0xe) * 3] + 0xc) = 0x808080;
  }
  return;
}

