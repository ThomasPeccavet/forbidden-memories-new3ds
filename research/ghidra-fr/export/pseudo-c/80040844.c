/* Analysis pseudo-C, not buildable source. */

void FUN_80040844(int param_1,undefined2 param_2,undefined2 param_3,int param_4,int param_5,
                 undefined1 param_6,undefined1 param_7,undefined1 param_8,undefined2 param_9,
                 undefined2 param_10)

{
  undefined2 uVar1;
  
  *(short *)(param_1 + 0x3c) = (short)param_4;
  *(undefined2 *)(param_1 + 0x30) = param_2;
  *(undefined2 *)(param_1 + 0x32) = param_3;
  uVar1 = (undefined2)(param_4 / 2);
  *(undefined2 *)(param_1 + 0x18) = uVar1;
  *(undefined2 *)(param_1 + 0x48) = uVar1;
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 8;
  *(short *)(param_1 + 0x3e) = (short)param_5;
  *(undefined1 *)(param_1 + 0x5c) = param_6;
  *(undefined1 *)(param_1 + 0x5d) = param_7;
  *(undefined1 *)(param_1 + 0x66) = param_8;
  *(undefined2 *)(param_1 + 0x40) = param_9;
  *(undefined2 *)(param_1 + 0x42) = param_10;
  uVar1 = (undefined2)(param_5 / 2);
  *(undefined2 *)(param_1 + 0x1a) = uVar1;
  *(undefined2 *)(param_1 + 0x4a) = uVar1;
  return;
}

