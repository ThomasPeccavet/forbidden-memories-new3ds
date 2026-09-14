/* Analysis pseudo-C, not buildable source. */

void FUN_80025f90(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_80024ee0();
  if (iVar1 == 0) {
    puVar2 = (undefined2 *)FUN_8002c860(0x12);
    *puVar2 = 0xa0;
    puVar2[1] = 0x78;
    puVar2[0xd] = 1;
    FUN_80040204(2);
  }
  else {
    DAT_8009c550 = 0;
  }
  return;
}

