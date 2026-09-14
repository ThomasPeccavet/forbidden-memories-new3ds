/* Analysis pseudo-C, not buildable source. */

void FUN_80044324(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &DAT_800f3c10;
  FUN_80073df8();
  iVar2 = 8;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
    FUN_80073db8(uVar1);
  } while (iVar2 != 0);
  FUN_80073e08();
  return;
}

