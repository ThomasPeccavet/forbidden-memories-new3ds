/* Analysis pseudo-C, not buildable source. */

void FUN_80016c48(int param_1,int param_2,undefined4 param_3,int param_4)

{
  char acStack_21 [9];
  
  FUN_80035ce8(param_3,param_4,acStack_21 + 1);
  while (-1 < param_4 + -1) {
    *(char *)(param_2 + 0xe) = acStack_21[param_4] << 3;
    FUN_80084978(param_2,*(undefined4 *)(&DAT_8009c858 + (uint)*(byte *)(param_1 + 0x17) * 4),
                 *(undefined2 *)(param_1 + 0x14));
    *(short *)(param_2 + 4) = *(short *)(param_2 + 4) + 8;
    param_4 = param_4 + -1;
  }
  return;
}

