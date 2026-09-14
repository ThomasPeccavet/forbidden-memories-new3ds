/* Analysis pseudo-C, not buildable source. */

void FUN_80042d58(int param_1)

{
  int iVar1;
  
  iVar1 = (int)CONCAT21(*(undefined2 *)(param_1 + 0x32),*(undefined1 *)(param_1 + 99)) +
          (int)*(short *)(param_1 + 0x38);
  *(char *)(param_1 + 99) = (char)iVar1;
  *(short *)(param_1 + 0x32) = (short)((uint)iVar1 >> 8);
  return;
}

