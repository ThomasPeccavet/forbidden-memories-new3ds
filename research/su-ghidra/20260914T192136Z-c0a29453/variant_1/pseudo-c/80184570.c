/* Analysis pseudo-C, not buildable source. */

void FUN_80184570(short param_1,short param_2,int param_3)

{
  uint uVar1;
  undefined1 auStack_30 [3];
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  short local_28;
  short local_26;
  undefined1 local_24;
  undefined1 local_23;
  ushort local_22;
  short local_20;
  short local_1e;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined2 local_1a;
  short local_18;
  short local_16;
  undefined1 local_14;
  undefined1 local_13;
  short local_10;
  short local_e;
  undefined1 local_c;
  undefined1 local_b;
  
  uVar1 = (int)(&DAT_801d4244)[param_3 + -1] >> 0x1a & 0x1f;
  if ((uVar1 == 0x14) || (uVar1 == 0x17)) {
    local_22 = 0x2f;
  }
  else if (uVar1 == 0x15) {
    local_22 = 0x30;
  }
  else {
    local_22 = 0x2e;
    if (uVar1 == 0x16) {
      local_22 = 0x31;
    }
  }
  local_2d = 9;
  local_29 = 0x2c;
  local_2c = 0x80;
  local_2b = 0x80;
  local_2a = 0x80;
  local_1a = 0xb;
  local_22 = local_22 | 0x3f00;
  local_20 = param_1 + 0x10;
  local_16 = param_2 + 0x10;
  local_23 = 0xc0;
  local_1b = 0xc0;
  local_13 = 0xd0;
  local_b = 0xd0;
  local_24 = 0;
  local_1c = 0x10;
  local_14 = 0;
  local_c = 0x10;
  local_28 = param_1;
  local_26 = param_2;
  local_1e = param_2;
  local_18 = param_1;
  local_10 = local_20;
  local_e = local_16;
  FUN_800842a8(auStack_30,DAT_8009c85c,0x20);
  return;
}

