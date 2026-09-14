/* Analysis pseudo-C, not buildable source. */

void FUN_8008b678(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)&DAT_0000df80;
  puVar2 = &DAT_8008b4dc;
  do {
    *puVar1 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (puVar2 != &DAT_8008b54c);
  return;
}

