/* Analysis pseudo-C, not buildable source. */

void FUN_8008f29c(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 unaff_retaddr;
  
  DAT_8009b22c = unaff_retaddr;
  if ((DAT_8009b228 != (undefined4 *)0x0) && (iVar1 = FUN_8008f328(), iVar1 != 0)) {
    puVar3 = (undefined4 *)0x8008f47c;
    puVar2 = DAT_8009b228;
    do {
      *puVar2 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (puVar3 != (undefined4 *)0x8008f488);
    FUN_80074638();
  }
  return;
}

