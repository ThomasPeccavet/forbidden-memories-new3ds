/* Analysis pseudo-C, not buildable source. */

void FUN_800193dc(int param_1)

{
  int iVar1;
  short sVar2;
  ushort *puVar3;
  
  do {
    iVar1 = FUN_8008288c(10);
  } while (iVar1 != 0);
  sVar2 = 0;
  if (DAT_8009c455 == '\0') {
    sVar2 = 0x140;
  }
  puVar3 = &DAT_8015c424;
  DAT_8009c838 = *(short *)(param_1 + 0x30) + sVar2;
  DAT_8009c83a = *(undefined2 *)(param_1 + 0x32);
  DAT_8009c83c = 0x8c;
  DAT_8009c83e = 0xd4;
  FUN_8008246c(&DAT_8009c838,&DAT_8015c424);
  iVar1 = 0x73f0;
  do {
    iVar1 = iVar1 + -1;
    *puVar3 = *puVar3 | 0x8000;
    puVar3 = puVar3 + 1;
  } while (iVar1 != 0);
  DAT_8016ac00 = 0;
  DAT_8016ac02 = 0;
  DAT_8016aaee = 0;
  DAT_8016aaec = 0;
  DAT_8016aaea = 0;
  DAT_8016a9d4 = 0;
  DAT_8015c652 = 0;
  DAT_8015c53c = 0;
  DAT_8015c538 = 0;
  DAT_8015c53a = 0;
  DAT_8015c426 = 0;
  DAT_8009c838 = 0x140;
  DAT_8009c83a = 0x100;
  DAT_8009c83c = 0x8c;
  DAT_8015c424 = 0;
  DAT_8009c83e = 0xd4;
  FUN_80082380();
  return;
}

