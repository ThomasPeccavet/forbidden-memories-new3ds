/* Analysis pseudo-C, not buildable source. */

void FUN_80042d30(int param_1)

{
  int iVar1;
  
  iVar1 = (int)CONCAT21(*(undefined2 *)(param_1 + 0x30),*(undefined1 *)(param_1 + 0x62)) +
          (int)*(short *)(param_1 + 0x36);
  *(char *)(param_1 + 0x62) = (char)iVar1;
  *(short *)(param_1 + 0x30) = (short)((uint)iVar1 >> 8);
  return;
}

