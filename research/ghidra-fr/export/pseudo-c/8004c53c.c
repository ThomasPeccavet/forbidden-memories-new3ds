/* Analysis pseudo-C, not buildable source. */

void FUN_8004c53c(undefined4 param_1)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = FUN_8004bfc4();
  uVar4 = 1;
  do {
    cVar2 = FUN_8004bf74(param_1);
    bVar1 = uVar4 < uVar3;
    if (cVar2 == -9) {
      return;
    }
    uVar4 = uVar4 + 1;
  } while (bVar1);
  return;
}

