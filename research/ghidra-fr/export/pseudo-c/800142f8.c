/* Analysis pseudo-C, not buildable source. */

void FUN_800142f8(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  puVar1 = &DAT_800eb200;
  puVar2 = &DAT_800eb1b8;
  do {
    puVar4 = puVar2;
    puVar3 = puVar1;
    uVar5 = puVar3[1];
    uVar6 = puVar3[2];
    uVar7 = puVar3[3];
    *puVar4 = *puVar3;
    puVar4[1] = uVar5;
    puVar4[2] = uVar6;
    puVar4[3] = uVar7;
    puVar1 = puVar3 + 4;
    puVar2 = puVar4 + 4;
  } while (puVar3 + 4 != (undefined4 *)0x800eb240);
  uVar5 = puVar3[5];
  puVar4[4] = uRam800eb240;
  puVar4[5] = uVar5;
  DAT_801d4200 = DAT_801d4220;
  DAT_801d4204 = DAT_801d4224;
  DAT_801d4208 = DAT_801d4228;
  DAT_801d420c = DAT_801d422c;
  DAT_801d4210 = DAT_801d4230;
  DAT_801d4214 = DAT_801d4234;
  DAT_801d4218 = DAT_801d4238;
  DAT_801d421c = DAT_801d423c;
  if (DAT_800eb1fe == '\x04') {
    DAT_8009c47c = DAT_8009c47c | 1;
  }
  DAT_8009c460 = DAT_800eb1e4 | 0x10;
  return;
}

