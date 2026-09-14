/* Analysis pseudo-C, not buildable source. */

void FUN_800230ac(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = *(undefined4 **)(param_1 + 8);
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = 0;
    puVar1 = puVar2 + 1;
    FUN_80023054(param_1,*(undefined4 *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
    do {
      FUN_80023054(param_1,*puVar2);
      FUN_80023054(param_1,*puVar1);
      if (param_2 != 0) {
        *puVar2 = 0;
        *puVar1 = 0;
      }
      puVar1 = puVar1 + 3;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 3;
    } while (iVar3 < 5);
  }
  return;
}

