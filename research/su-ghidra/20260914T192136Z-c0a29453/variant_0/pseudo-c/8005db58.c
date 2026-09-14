/* Analysis pseudo-C, not buildable source. */

void FUN_8005db58(int *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18;
  undefined4 *local_14;
  
  if (*param_1 == 0x3800000) {
    *(code **)param_1[1] = FUN_8005dca4;
    cVar1 = FUN_80089d60(param_2 + (uint)*(byte *)(param_2 + 0xe1b) * 4 + 0x1e0,param_1[1]);
    iVar2 = FUN_80089cb8(param_1[1],0);
    if (iVar2 != 0) {
      while (iVar2 = FUN_80089cb8(0,&local_18), iVar2 != 0) {
        uVar3 = FUN_8005dc2c(local_18);
        *local_14 = uVar3;
      }
      *(char *)(param_2 + 0xe1b) = *(char *)(param_2 + 0xe1b) + cVar1;
    }
  }
  else {
    FUN_8008fa78(s_unsupported_ANIMATION_primitive_0_800116f4);
    *(undefined1 **)param_1[1] = &LAB_80089da8;
  }
  return;
}

