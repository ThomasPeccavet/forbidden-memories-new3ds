/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8005c4d8(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 auStack_40 [32];
  undefined4 local_20 [2];
  
  iVar1 = *(int *)(*(int *)(*(int *)(&DAT_800f417c + param_1 * 0xe20 + (param_2 + 1) * 8) + 4) + 8);
  FUN_80087158();
  FUN_8008a428(*(int *)(&DAT_800f4e8c + param_1 * 0xe20) + param_2 * 0x50,auStack_40);
  FUN_80085558(auStack_40);
  FUN_800878f8(iVar1 + param_3 * 8,param_4,local_20);
  FUN_800871fc();
  return local_20[0];
}

