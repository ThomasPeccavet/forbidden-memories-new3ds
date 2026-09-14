/* Analysis pseudo-C, not buildable source. */

undefined2 * FUN_80074e5c(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar2 = (undefined2 *)0x0;
  if (DAT_80092e20 != 0) {
    FUN_80073df8();
    puVar1 = DAT_80093eb0;
    puVar2 = DAT_80093eac;
    DAT_80092e52 = *DAT_80093eb0;
    DAT_80092e54 = *DAT_80093eb4;
    *DAT_80093eb0 = 0;
    *puVar2 = *puVar1;
    *DAT_80093eb4 = *DAT_80093eb4 & 0x77777777;
    FUN_80074fc8();
    DAT_80092e20 = 0;
    puVar2 = &DAT_80092e20;
  }
  return puVar2;
}

