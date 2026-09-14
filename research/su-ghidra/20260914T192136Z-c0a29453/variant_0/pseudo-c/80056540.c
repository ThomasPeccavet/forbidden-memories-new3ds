/* Analysis pseudo-C, not buildable source. */

void FUN_80056540(void)

{
  int iVar1;
  undefined2 *puVar2;
  ushort *puVar3;
  undefined2 local_210;
  undefined2 local_20e [255];
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  
  puVar2 = local_20e;
  iVar1 = 0xfe;
  local_210 = 0;
  do {
    *puVar2 = 0xffff;
    iVar1 = iVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (-1 < iVar1);
  local_10 = 0x280;
  local_e = 0xf0;
  local_c = 0x100;
  local_a = 1;
  do {
    iVar1 = FUN_8008288c(3);
  } while (iVar1 != 0);
  do {
    iVar1 = FUN_80082380(&local_10,&local_210);
  } while (iVar1 != 0);
  do {
    iVar1 = FUN_8008288c(3);
  } while (iVar1 != 0);
  FUN_80059294(0);
  FUN_80059294(1);
  FUN_80059294(2);
  iVar1 = 0;
  puVar3 = &DAT_800f4088;
  do {
    iVar1 = iVar1 + 1;
    *puVar3 = *puVar3 & 0xfffe;
    puVar3 = puVar3 + 0xc;
  } while (iVar1 < 10);
  DAT_8009c32b = 0;
  DAT_8009c32c = 0;
  FUN_8005cbe8(0x8000);
  DAT_8009c324 = 0;
  DAT_8009c32a = 0xff;
  return;
}

