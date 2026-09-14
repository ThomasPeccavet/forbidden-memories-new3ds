/* Analysis pseudo-C, not buildable source. */

void FUN_80086178(undefined4 *param_1,short param_2,undefined2 param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = DAT_800ff4f8;
  uVar1 = DAT_800ff4f4;
  *param_1 = DAT_800ff4f0;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  uVar2 = DAT_800ff504;
  uVar1 = DAT_800ff500;
  param_1[3] = DAT_800ff4fc;
  param_1[4] = uVar1;
  param_1[5] = uVar2;
  uVar1 = DAT_800ff50c;
  param_1[6] = DAT_800ff508;
  param_1[7] = uVar1;
  switch((param_4 + -0x58) * 0x1000000 >> 0x18) {
  case 0:
  case 0x20:
    *(undefined2 *)(param_1 + 2) = param_3;
    *(undefined2 *)(param_1 + 4) = param_3;
    *(short *)((int)param_1 + 10) = -param_2;
    *(short *)((int)param_1 + 0xe) = param_2;
    break;
  case 1:
  case 0x21:
    *(undefined2 *)param_1 = param_3;
    *(undefined2 *)(param_1 + 4) = param_3;
    *(short *)(param_1 + 1) = param_2;
    *(short *)(param_1 + 3) = -param_2;
    break;
  case 2:
  case 0x22:
    *(undefined2 *)param_1 = param_3;
    *(undefined2 *)(param_1 + 2) = param_3;
    *(short *)((int)param_1 + 2) = -param_2;
    *(short *)((int)param_1 + 6) = param_2;
  }
  return;
}

