/* Analysis pseudo-C, not buildable source. */

void FUN_80044378(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  DAT_8009c7ca = 0xff;
  DAT_8009c7cb = 0;
  DAT_8009c7c0 = 0;
  puVar3 = &DAT_800f3c10;
  FUN_80073df8();
  DAT_800f3c10 = FUN_80073da8(0xf4000001,4,0x1000,&LAB_800451b8);
  DAT_800f3c14 = FUN_80073da8(0xf4000001,0x100,0x1000,&LAB_800451c8);
  DAT_800f3c18 = FUN_80073da8(0xf4000001,0x8000,0x1000,&LAB_800451dc);
  DAT_800f3c1c = FUN_80073da8(0xf4000001,0x2000,0x1000,&LAB_800451f0);
  DAT_800f3c20 = FUN_80073da8(0xf0000011,4,0x1000,&LAB_800451b8);
  DAT_800f3c24 = FUN_80073da8(0xf0000011,0x100,0x1000,&LAB_800451c8);
  DAT_800f3c28 = FUN_80073da8(0xf0000011,0x8000,0x1000,&LAB_800451dc);
  DAT_800f3c2c = FUN_80073da8(0xf0000011,0x2000,0x1000,&LAB_800451f0);
  iVar2 = 8;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
    FUN_80073dd8(uVar1);
  } while (iVar2 != 0);
  FUN_80073e08();
  return;
}

