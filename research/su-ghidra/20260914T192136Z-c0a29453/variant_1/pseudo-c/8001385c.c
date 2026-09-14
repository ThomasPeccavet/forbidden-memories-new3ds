/* Analysis pseudo-C, not buildable source. */

void FUN_8001385c(int param_1,uint param_2,int param_3,int param_4)

{
  *(int *)(param_1 + 0x10) = param_4;
  if (param_4 < 0) {
    *(int *)(param_1 + 0x10) = param_4 * -0x800;
  }
  if (param_3 < 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(int *)(param_1 + 0x24) = -param_3;
    return;
  }
  *(int *)(param_1 + 0x14) = param_3 << 0xb;
  *(int *)(param_1 + 0x24) = (&DAT_800eb198)[param_2 & 0xf] + param_3;
  return;
}

