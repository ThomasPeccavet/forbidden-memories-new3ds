/* Analysis pseudo-C, not buildable source. */

void FUN_8005c698(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                 undefined1 param_5)

{
  int iVar1;
  
  iVar1 = param_1 * 0xe20;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 3) = param_2;
  *(undefined1 *)(&DAT_800f4f38 + param_1 * 0x388) = param_3;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 1) = param_4;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 2) = param_5;
  return;
}

