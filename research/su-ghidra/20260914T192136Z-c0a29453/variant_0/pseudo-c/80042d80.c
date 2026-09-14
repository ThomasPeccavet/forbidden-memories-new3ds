/* Analysis pseudo-C, not buildable source. */

void FUN_80042d80(int param_1)

{
  int iVar1;
  
  iVar1 = (int)CONCAT21(*(undefined2 *)(param_1 + 0x34),*(undefined1 *)(param_1 + 100)) +
          (int)*(short *)(param_1 + 0x3a);
  *(char *)(param_1 + 100) = (char)iVar1;
  *(short *)(param_1 + 0x34) = (short)((uint)iVar1 >> 8);
  return;
}

