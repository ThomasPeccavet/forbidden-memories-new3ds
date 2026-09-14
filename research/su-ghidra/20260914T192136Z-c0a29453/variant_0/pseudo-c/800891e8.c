/* Analysis pseudo-C, not buildable source. */

undefined4
FUN_800891e8(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5,undefined4 *param_6,undefined4 *param_7,undefined4 *param_8,
            undefined4 *param_9,undefined4 param_10,undefined4 param_11,int param_12)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [8];
  
  *(int *)(param_12 + 0xf0) = param_12 + 0x18;
  *(int *)(param_12 + 0xf4) = param_12 + 0x30;
  *(int *)(param_12 + 0xf8) = param_12 + 0x48;
  *(int *)(param_12 + 0xfc) = param_12 + 0x60;
  uVar2 = param_1[1];
  *(undefined4 *)(param_12 + 0x18) = *param_1;
  *(undefined4 *)(param_12 + 0x1c) = uVar2;
  uVar2 = param_2[1];
  *(undefined4 *)(param_12 + 0x30) = *param_2;
  *(undefined4 *)(param_12 + 0x34) = uVar2;
  uVar2 = param_3[1];
  *(undefined4 *)(param_12 + 0x48) = *param_3;
  *(undefined4 *)(param_12 + 0x4c) = uVar2;
  uVar2 = param_4[1];
  *(undefined4 *)(param_12 + 0x60) = *param_4;
  *(undefined4 *)(param_12 + 100) = uVar2;
  iVar1 = FUN_80087b48(param_12 + 0x18,param_12 + 0x30,param_12 + 0x48,param_12 + 0x60,
                       param_12 + 0x28,param_12 + 0x40,param_12 + 0x58,param_12 + 0x70,auStack_38,
                       auStack_34,auStack_30);
  if (0 < iVar1) {
    FUN_800893e8(param_12 + 0x2c,param_12 + 0x44,param_12 + 0x5c,param_12 + 0x74);
    *(undefined4 *)(param_12 + 0x14) = param_11;
    *(undefined4 *)(param_12 + 0x10) = *param_9;
    *(undefined2 *)(param_12 + 0xc) = *(undefined2 *)((int)param_5 + 2);
    *(undefined2 *)(param_12 + 0xe) = *(undefined2 *)((int)param_6 + 2);
    *(undefined4 *)(param_12 + 0x20) = *param_5;
    *(undefined4 *)(param_12 + 0x38) = *param_6;
    *(undefined4 *)(param_12 + 0x50) = *param_7;
    *(undefined4 *)(param_12 + 0x68) = *param_8;
    param_10 = FUN_80089410(param_10,param_12,0,param_12 + 0x78);
  }
  return param_10;
}

