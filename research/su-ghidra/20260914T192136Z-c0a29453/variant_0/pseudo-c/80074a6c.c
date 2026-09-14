/* Analysis pseudo-C, not buildable source. */

undefined2 * FUN_80074a6c(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  puVar2 = DAT_80093eb0;
  puVar1 = DAT_80093eac;
  puVar3 = (undefined2 *)0x0;
  if (DAT_80092e20 == 0) {
    *DAT_80093eb0 = 0;
    *puVar1 = *puVar2;
    *DAT_80093eb4 = 0x33333333;
    FUN_80074f74(&DAT_80092e20,0x41a);
    iVar4 = FUN_80090d58(&DAT_80092e58);
    if (iVar4 != 0) {
      FUN_80074b44();
    }
    DAT_80092e5c = &DAT_80093e38;
    FUN_80074fd8(&DAT_80092e58);
    DAT_80092e20 = 1;
    uVar5 = FUN_80074fe8();
    *(undefined4 *)(PTR_PTR_80093ea8 + 0x14) = uVar5;
    uVar5 = FUN_80075108();
    *(undefined4 *)(PTR_PTR_80093ea8 + 4) = uVar5;
    FUN_80074fa0();
    puVar3 = &DAT_80092e20;
    FUN_80073e08();
  }
  return puVar3;
}

