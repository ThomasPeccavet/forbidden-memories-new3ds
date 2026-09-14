/* Analysis pseudo-C, not buildable source. */

void FUN_80086088(uint *param_1,uint *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar2 = *param_1;
  *param_2 = uVar2;
  if ((uVar2 >> 3 & 1) == 0) {
    *(short *)(param_2 + 1) = (short)param_1[2];
    *(undefined2 *)((int)param_2 + 6) = *(undefined2 *)((int)param_1 + 10);
    *(short *)(param_2 + 2) = (short)param_1[3];
    uVar1 = *(undefined2 *)((int)param_1 + 0xe);
    param_2[3] = (uint)(param_1 + 4);
    *(undefined2 *)((int)param_2 + 10) = uVar1;
  }
  else {
    puVar3 = param_1 + 1;
    uVar2 = *puVar3 & 0xfffffffc;
    *(short *)(param_2 + 4) = (short)param_1[2];
    *(undefined2 *)((int)param_2 + 0x12) = *(undefined2 *)((int)param_1 + 10);
    *(short *)(param_2 + 5) = (short)param_1[3];
    uVar1 = *(undefined2 *)((int)param_1 + 0xe);
    param_2[6] = (uint)(param_1 + 4);
    *(undefined2 *)((int)param_2 + 0x16) = uVar1;
    *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)puVar3 + uVar2 + 4);
    *(undefined2 *)((int)param_2 + 6) = *(undefined2 *)((int)puVar3 + uVar2 + 6);
    *(undefined2 *)(param_2 + 2) = *(undefined2 *)((int)puVar3 + uVar2 + 8);
    uVar1 = *(undefined2 *)((int)puVar3 + uVar2 + 10);
    param_2[3] = (int)puVar3 + uVar2 + 0xc;
    *(undefined2 *)((int)param_2 + 10) = uVar1;
  }
  return;
}

