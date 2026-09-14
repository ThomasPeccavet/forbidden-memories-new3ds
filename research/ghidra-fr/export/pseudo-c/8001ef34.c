/* Analysis pseudo-C, not buildable source. */

uint FUN_8001ef34(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x6a);
  puVar7 = &DAT_801a7ad8 + uVar1 * 7;
  if (param_2 == 0) {
    uVar2 = FUN_80016fe4(puVar7);
    uVar2 = uVar2 & 0xffff;
  }
  else {
    uVar3 = (uint)*(byte *)(param_2 + 0x6a);
    puVar5 = &DAT_801a7ad8 + uVar3 * 7;
    uVar4 = FUN_80016fe4(puVar5);
    uVar6 = uVar4 & 0xffff;
    if (((&DAT_801a7aee)[uVar3 * 0xe] & 0x800) != 0) {
      uVar6 = uVar4 >> 0x10;
    }
    if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x800) == 0) {
      uVar4 = FUN_8001ee7c(puVar7,puVar5);
    }
    else {
      uVar4 = FUN_8001eed8(puVar7,puVar5);
    }
    uVar2 = uVar4 - uVar6;
    if (((uVar4 == uVar6) && (uVar2 = 0, ((&DAT_801a7aee)[uVar1 * 0xe] & 0x800) == 0)) &&
       (uVar2 = 0, ((&DAT_801a7aee)[uVar3 * 0xe] & 0x800) == 0)) {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

