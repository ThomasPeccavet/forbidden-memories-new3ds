/* Analysis pseudo-C, not buildable source. */

void FUN_80049100(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = 0;
  do {
    uVar1 = uVar1 + 1;
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_2[3];
    param_1[4] = param_2[4];
    param_1[5] = param_2[5];
    puVar2 = param_2 + 7;
    param_1[6] = param_2[6];
    param_2 = param_2 + 8;
    param_1[7] = *puVar2;
    param_1 = param_1 + 8;
  } while (uVar1 < 0x40);
  return;
}

