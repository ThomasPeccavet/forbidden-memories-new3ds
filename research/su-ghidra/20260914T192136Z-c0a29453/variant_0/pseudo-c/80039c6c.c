/* Analysis pseudo-C, not buildable source. */

void FUN_80039c6c(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_80039a88();
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 0x13) = 1;
    *(undefined1 *)(param_1 + 10) = 0;
    *(undefined1 *)(param_1 + 0xb) = 0;
    *(undefined1 *)(param_1 + 0xc) = 0;
    *(char *)(param_1 + 6) =
         (char)((int)((uint)*(ushort *)(param_1 + 2) << 0x10) >> 0x14) +
         (char)((int)((uint)*(ushort *)(param_1 + 4) << 0x10) >> 0x13) + '\x01';
  }
  if ((*(byte *)(param_1 + 0x11) & 0x40) == 0) {
    cVar1 = *(char *)(param_1 + 6) + -1;
    *(char *)(param_1 + 6) = cVar1;
    if (cVar1 == '\0') {
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x40;
    }
  }
  else {
    uVar4 = *(byte *)(param_1 + 10) + 4;
    uVar2 = (undefined1)uVar4;
    *(undefined1 *)(param_1 + 0xc) = uVar2;
    *(undefined1 *)(param_1 + 0xb) = uVar2;
    *(undefined1 *)(param_1 + 10) = uVar2;
    if (0x3f < uVar4) {
      FUN_80039ab0(param_1);
    }
  }
  return;
}

