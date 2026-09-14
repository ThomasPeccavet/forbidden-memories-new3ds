/* Analysis pseudo-C, not buildable source. */

void FUN_8005d570(int param_1,undefined1 param_2)

{
  int iVar1;
  int *piVar2;
  
  param_1 = param_1 * 0xe20;
  piVar2 = (int *)(&DAT_800f4358 + param_1);
  iVar1 = 0;
  if ((&DAT_800f4f93)[param_1] != '\0') {
    do {
      *(undefined1 *)(*piVar2 + 0xd) = param_2;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < (int)(uint)(byte)(&DAT_800f4f93)[param_1]);
  }
  return;
}

