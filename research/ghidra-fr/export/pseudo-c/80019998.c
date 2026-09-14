/* Analysis pseudo-C, not buildable source. */

uint FUN_80019998(uint param_1,uint param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  
  puVar1 = &DAT_8017a1d8;
  while( true ) {
    if (*puVar1 == 0) {
      return 0;
    }
    uVar3 = (uint)puVar1[1];
    puVar2 = puVar1 + 2;
    if (*puVar1 == param_1) break;
    puVar1 = puVar2 + uVar3;
  }
  do {
    uVar3 = uVar3 - 1;
    if (param_2 == *puVar2) {
      return param_2;
    }
    puVar2 = puVar2 + 1;
  } while (uVar3 != 0);
  return 0;
}

