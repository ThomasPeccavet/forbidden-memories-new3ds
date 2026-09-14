/* Analysis pseudo-C, not buildable source. */

int * FUN_80084018(int *param_1,int param_2,uint param_3,byte param_4)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (param_3 & 0xffff) - *(int *)(param_2 + 8);
  if (iVar2 < 0) {
    FUN_8008fa78(s_ps_sort_sprite_bg__z_resolution_o_800122ac);
  }
  piVar1 = (int *)(*(int *)(param_2 + 4) + iVar2 * 4);
  *param_1 = *piVar1;
  *(byte *)((int)param_1 + 3) = param_4;
  *piVar1 = (int)param_1;
  *(undefined1 *)((int)piVar1 + 3) = 0;
  return param_1 + param_4 + 1;
}

