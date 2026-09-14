/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80077108(uint param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int local_28;
  
  local_28 = 0;
  if (param_1 < 10) {
    iVar4 = FUN_800762c8((&DAT_80094548)[param_1]);
    iVar3 = DAT_80093fd4;
    if (iVar4 == 0) {
      if (param_1 == 0) {
        uVar6 = 0x10 << (DAT_80093fe0 & 0x1f);
        iVar4 = 0xfff0 << (DAT_80093fe0 & 0x1f);
      }
      else {
        iVar4 = (&DAT_80094548)[param_1];
        uVar6 = 0x10000 - iVar4 << (DAT_80093fe0 & 0x1f);
        iVar4 = iVar4 << (DAT_80093fe0 & 0x1f);
      }
      bVar1 = DAT_80093fd4 == 1;
      if (bVar1) {
        DAT_80093fd4 = 0;
      }
      bVar2 = true;
      if (DAT_80093ff0 != 0) {
        local_28 = DAT_80093ff0;
        DAT_80093ff0 = 0;
      }
      do {
        uVar5 = 0x400;
        if (uVar6 < 0x401) {
          bVar2 = false;
          uVar5 = uVar6;
        }
        FUN_80075afc(2,iVar4);
        FUN_80075afc(1);
        FUN_80075afc(3,&DAT_80094028,uVar5);
        uVar6 = uVar6 - 0x400;
        iVar4 = iVar4 + 0x400;
        FUN_800772a8(DAT_80093f40);
      } while (bVar2);
      if (bVar1) {
        DAT_80093fd4 = iVar3;
      }
      if (local_28 == 0) {
        return 0;
      }
      DAT_80093ff0 = local_28;
      return 0;
    }
  }
  return 0xffffffff;
}

