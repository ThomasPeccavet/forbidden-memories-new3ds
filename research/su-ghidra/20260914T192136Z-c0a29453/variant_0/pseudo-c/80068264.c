/* Analysis pseudo-C, not buildable source. */

uint FUN_80068264(uint param_1,uint param_2,uint param_3)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_30;
  undefined2 local_2c;
  ushort local_2a;
  byte local_28;
  byte local_27;
  byte local_26;
  
  uVar4 = param_1 & 0xffff;
  uVar2 = 0;
  if (uVar4 != 0) {
    uVar2 = param_2 & 7;
    bVar1 = uVar2 == 6;
    FUN_80067d88(&local_30,param_1 & 0x1f,uVar4 >> 5 & 0x1f,uVar4 >> 10 & 0x1f,0x1f);
    if (uVar2 < 7) {
      if ((param_2 & 8) != 0) {
        uVar2 = (uVar2 + 3) % 6;
      }
      local_30 = uVar2 << 0xc;
    }
    if (bVar1) {
      local_2a = 0;
    }
    else {
      iVar3 = (uint)local_2a * (param_3 & 0xffff);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0xfff;
      }
      local_2a = (ushort)(iVar3 >> 0xc);
    }
    FUN_80067f9c(&local_28,local_30,local_2c,local_2a,0x1f);
    if ((param_2 & 8) != 0) {
      local_28 = 0x1f - local_28;
      local_26 = 0x1f - local_26;
      local_27 = 0x1f - local_27;
    }
    if (local_28 == 0) {
      local_28 = 1;
    }
    if (local_27 == 0) {
      local_27 = 1;
    }
    if (local_26 == 0) {
      local_26 = 1;
    }
    uVar2 = local_28 & 0x1f | (local_27 & 0x1f) << 5 | (local_26 & 0x1f) << 10 | param_1 & 0x8000;
  }
  return uVar2;
}

