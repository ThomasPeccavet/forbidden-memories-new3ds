/* Analysis pseudo-C, not buildable source. */

void FUN_800322b8(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 + param_2;
  cVar1 = *(char *)(iVar3 + 0x5d97);
  if (cVar1 == '\0') {
    *(int *)(param_1 + 0x5a9c) = *(int *)(param_1 + 0x5a9c) + 1;
    *(char *)(iVar3 + 0x5d97) = *(char *)(iVar3 + 0x5d97) + '\x01';
    iVar3 = param_1 + 4;
    do {
      iVar2 = iVar3;
      iVar3 = iVar2 + 0x10;
    } while (*(short *)(iVar2 + 4) != param_2);
    *(undefined1 *)(iVar2 + 0xd) = 1;
    FUN_80033144(param_1 + 4);
  }
  else if (cVar1 != -6) {
    *(char *)(iVar3 + 0x5d97) = cVar1 + '\x01';
    *(int *)(param_1 + 0x5a9c) = *(int *)(param_1 + 0x5a9c) + 1;
  }
  return;
}

