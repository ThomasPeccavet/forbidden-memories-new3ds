/* Analysis pseudo-C, not buildable source. */

void FUN_800753f8(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  FUN_800748d8();
  FUN_80075558(param_1);
  if (param_1 == 0) {
    iVar2 = 0x17;
    puVar1 = &DAT_80093fa2;
    do {
      *puVar1 = 0xc000;
      iVar2 = iVar2 + -1;
      puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
  }
  FUN_800754e0();
  DAT_80093f4c = 0;
  DAT_80093f50 = 0;
  DAT_80093f5c = 0;
  DAT_80093f60 = 0;
  DAT_80093f62 = 0;
  DAT_80093f64 = 0;
  DAT_80093f68 = 0;
  DAT_80093f54 = DAT_80094548;
  FUN_80075e64(0xd1,DAT_80094548,0);
  DAT_80094018 = 0;
  DAT_8009401c = 0;
  DAT_80094020 = 0;
  DAT_80093f48 = 0;
  DAT_80093fd4 = 0;
  DAT_80093f44 = 0;
  DAT_80093f70 = 0;
  DAT_80093f6c = 0;
  DAT_80093fa4 = 0;
  return;
}

