/* Analysis pseudo-C, not buildable source. */

void FUN_8008f6c8(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (param_3 != 0) {
    do {
      puVar2 = (undefined1 *)(param_1 + uVar4);
      puVar3 = (undefined1 *)(param_2 + uVar4);
      uVar1 = *puVar2;
      uVar4 = uVar4 + 1;
      *puVar2 = *puVar3;
      *puVar3 = uVar1;
    } while (uVar4 < param_3);
  }
  return;
}

