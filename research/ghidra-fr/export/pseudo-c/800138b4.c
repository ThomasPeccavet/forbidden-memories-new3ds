/* Analysis pseudo-C, not buildable source. */

int FUN_800138b4(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5,
                undefined4 param_6,undefined4 param_7,int param_8)

{
  int iVar1;
  int unaff_gp;
  
  *(undefined4 *)(param_1 + 0x18) = param_3;
  FUN_8001385c(param_1,param_2,param_4,-param_5);
  *(undefined1 *)(param_1 + 0x46) = 1;
  *(undefined1 *)(param_1 + 0x47) = 0;
  *(undefined2 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = param_6;
  *(undefined4 *)(param_1 + 0x40) = param_7;
  if (param_8 != 0) {
    if ((param_2 & 0x1000000) == 0) {
      *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x10);
      if (param_8 < 0) {
        *(undefined1 *)(param_1 + 0x46) = 1;
        *(int *)(param_1 + 0xc) = param_8;
        *(int *)(param_1 + 8) = param_8;
      }
      else {
        param_2 = param_2 | 0x10000;
        *(undefined1 *)(param_1 + 0x46) = 2;
        *(short *)(param_1 + 0x32) = (short)((uint)param_8 >> 0x10);
        *(undefined2 *)(param_1 + 4) = 0x40;
        iVar1 = *(int *)(unaff_gp + 0x218);
        *(short *)(param_1 + 0x30) = (short)param_8;
        *(undefined2 *)(param_1 + 6) = 0x10;
        *(int *)(param_1 + 8) = iVar1;
        *(int *)(param_1 + 0xc) = iVar1 + 0x800;
      }
    }
    else {
      *(int *)(param_1 + 0x34) = param_8;
    }
  }
  *(uint *)(param_1 + 0x2c) = param_2;
  return param_1;
}

