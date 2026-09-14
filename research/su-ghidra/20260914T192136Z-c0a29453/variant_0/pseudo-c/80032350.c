/* Analysis pseudo-C, not buildable source. */

void FUN_80032350(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)*(byte *)(param_1 + param_2 + 0x5d97);
  iVar3 = uVar2 - 1;
  if (uVar2 != 0) {
    iVar1 = param_1 + 4;
    if (iVar3 == 0) {
      for (; *(short *)(iVar1 + 4) != param_2; iVar1 = iVar1 + 0x10) {
      }
      *(undefined1 *)(iVar1 + 0xd) = 0;
      if (*(char *)(param_1 + param_2 + 0x5d97) != '\0') {
        *(undefined1 *)(iVar1 + 0xd) = 0x80;
      }
      FUN_80033144(param_1 + 4);
    }
    *(char *)(param_1 + param_2 + 0x5d97) = (char)iVar3;
    *(int *)(param_1 + 0x5a9c) = *(int *)(param_1 + 0x5a9c) + -1;
  }
  return;
}

