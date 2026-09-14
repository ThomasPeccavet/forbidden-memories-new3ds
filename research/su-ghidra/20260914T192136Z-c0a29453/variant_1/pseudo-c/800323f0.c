/* Analysis pseudo-C, not buildable source. */

void FUN_800323f0(int param_1)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  *(undefined1 *)(param_1 + 0x5ac4) = 0;
  iVar4 = 1;
  iVar2 = param_1;
  do {
    *(undefined1 *)(iVar2 + 0x5ac5) = 0;
    iVar3 = 0;
    psVar1 = (short *)(param_1 + 0x2d54);
    do {
      if ((*(char *)((int)psVar1 + 9) != '\0') && (*psVar1 == iVar4)) {
        *(char *)(iVar2 + 0x5ac5) = *(char *)(iVar2 + 0x5ac5) + '\x01';
      }
      iVar3 = iVar3 + 1;
      psVar1 = psVar1 + 8;
    } while (iVar3 < 0x28);
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + 1;
  } while (iVar4 < 0x2d3);
  iVar2 = param_1 + 0x2d50;
  iVar4 = 0;
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    if (*(char *)(iVar2 + 0xd) == '\0') break;
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + 0x10;
  } while (iVar3 < 0x28);
  *(int *)(param_1 + 0x5aa0) = iVar4;
  return;
}

