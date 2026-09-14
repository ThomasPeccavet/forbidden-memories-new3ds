/* Analysis pseudo-C, not buildable source. */

void FUN_80086528(int param_1,int param_2)

{
  int local_20;
  int local_1c;
  int local_18;
  
  FUN_80086ff8(param_1,param_2 + 0x14,&local_20);
  FUN_80087408(param_1,param_2);
  *(int *)(param_2 + 0x14) = local_20 + *(int *)(param_1 + 0x14);
  *(int *)(param_2 + 0x18) = local_1c + *(int *)(param_1 + 0x18);
  *(int *)(param_2 + 0x1c) = local_18 + *(int *)(param_1 + 0x1c);
  return;
}

