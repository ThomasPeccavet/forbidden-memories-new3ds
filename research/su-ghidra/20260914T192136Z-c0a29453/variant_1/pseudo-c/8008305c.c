/* Analysis pseudo-C, not buildable source. */

int FUN_8008305c(int *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  if (*param_1 == 0x10) {
    puVar4 = (uint *)(param_1 + 2);
    *param_2 = param_1[1];
    iVar1 = FUN_8007fb5c();
    if (iVar1 == 2) {
      FUN_8008fa78(s_id___08x_8001227c,0x10);
    }
    iVar1 = FUN_8007fb5c();
    if (iVar1 == 2) {
      FUN_8008fa78(s_mode__08x_80012288,*param_2);
    }
    iVar1 = FUN_8007fb5c();
    if (iVar1 == 2) {
      FUN_8008fa78(s_timaddr__08x_80012294,puVar4);
    }
    if ((*param_2 & 8) == 0) {
      uVar3 = 0;
      param_2[1] = 0;
      param_2[2] = 0;
    }
    else {
      uVar3 = *puVar4;
      param_2[1] = (uint)(param_1 + 3);
      param_2[2] = (uint)(param_1 + 5);
      uVar3 = uVar3 >> 2;
      puVar4 = puVar4 + uVar3;
    }
    uVar2 = *puVar4;
    param_2[3] = (uint)(puVar4 + 1);
    param_2[4] = (uint)(puVar4 + 3);
    iVar1 = uVar3 + (uVar2 >> 2) + 2;
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}

