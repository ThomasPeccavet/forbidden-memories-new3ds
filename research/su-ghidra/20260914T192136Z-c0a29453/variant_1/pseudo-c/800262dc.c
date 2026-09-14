/* Analysis pseudo-C, not buildable source. */

void FUN_800262dc(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_80024ee0();
  if (iVar1 == 0) {
    DAT_8009c59e = FUN_8002c9bc(0,(int)DAT_8009c5c4);
    if (DAT_8009c59e != 0) {
      puVar2 = (undefined2 *)FUN_8002c860(0x12);
      *puVar2 = 0xa0;
      puVar2[1] = 0x78;
      puVar2[0xd] = 1;
      FUN_80040204(2);
      FUN_800292dc(1,(int)DAT_8009c59e);
    }
  }
  else if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
    DAT_8009c550 = 0;
  }
  return;
}

