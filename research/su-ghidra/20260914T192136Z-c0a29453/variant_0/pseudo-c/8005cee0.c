/* Analysis pseudo-C, not buildable source. */

void FUN_8005cee0(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined *puVar3;
  
  param_1 = param_1 * 0xe20;
  puVar3 = &DAT_800f4178 + param_1;
  if (((&DAT_800f4f97)[param_1] != '\0') && (iVar2 = 0, (&DAT_800f4f92)[param_1] != '\0')) {
    do {
      piVar1 = *(int **)(puVar3 + 4);
      if (piVar1 != (int *)0x0) {
        do {
          if (piVar1[2] != 0) {
            FUN_8005d644(&LAB_8006865c,piVar1 + 3,piVar1[1]);
          }
          piVar1 = (int *)*piVar1;
        } while (piVar1 != (int *)0xffffffff);
      }
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 8;
    } while (iVar2 < (int)(uint)(byte)(&DAT_800f4f92)[param_1]);
  }
  return;
}

