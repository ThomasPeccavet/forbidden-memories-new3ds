/* Analysis pseudo-C, not buildable source. */

char * FUN_800684b0(char *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                   uint param_5,ushort param_6,char param_7)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int local_30;
  undefined2 local_2c;
  ushort local_2a;
  char local_28;
  char local_27;
  char local_26;
  
  uVar3 = param_5 & 7;
  bVar1 = uVar3 == 6;
  FUN_80067d88(&local_30,param_2,param_3,param_4,param_7);
  if (uVar3 < 7) {
    if ((param_5 & 8) != 0) {
      uVar3 = (uVar3 + 3) % 6;
    }
    local_30 = uVar3 << 0xc;
  }
  if (bVar1) {
    local_2a = 0;
  }
  else {
    iVar2 = (uint)local_2a * (uint)param_6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xfff;
    }
    local_2a = (ushort)(iVar2 >> 0xc);
  }
  FUN_80067f9c(&local_28,local_30,local_2c,local_2a,param_7);
  if ((param_5 & 8) != 0) {
    local_28 = param_7 - local_28;
    local_26 = param_7 - local_26;
    local_27 = param_7 - local_27;
  }
  if (local_28 == '\0') {
    local_28 = '\x01';
  }
  if (local_27 == '\0') {
    local_27 = '\x01';
  }
  if (local_26 == '\0') {
    local_26 = '\x01';
  }
  *param_1 = local_28;
  param_1[1] = local_27;
  param_1[2] = local_26;
  return param_1;
}

