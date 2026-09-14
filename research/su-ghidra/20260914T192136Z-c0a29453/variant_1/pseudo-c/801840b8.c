/* Analysis pseudo-C, not buildable source. */

void FUN_801840b8(short param_1,short param_2,int param_3)

{
  short sVar1;
  int iVar2;
  undefined1 auStack_50 [3];
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  short local_48;
  short local_46;
  char local_44;
  undefined1 local_43;
  undefined2 local_42;
  short local_40;
  short local_3e;
  char local_3c;
  undefined1 local_3b;
  undefined2 local_3a;
  short local_38;
  short local_36;
  char local_34;
  undefined1 local_33;
  short local_30;
  short local_2e;
  char local_2c;
  undefined1 local_2b;
  
  iVar2 = 0;
  sVar1 = -0x18;
  local_4d = 9;
  local_49 = 0x2c;
  local_3a = 10;
  local_42 = 0x3168;
  local_4c = 0x80;
  local_4b = 0x80;
  local_4a = 0x80;
  do {
    local_40 = param_1 - sVar1;
    sVar1 = sVar1 + 8;
    iVar2 = iVar2 + 1;
    local_48 = local_40 + -0xc;
    local_40 = local_40 + -4;
    local_43 = 0x40;
    local_3b = 0x40;
    local_33 = 0x48;
    local_2b = 0x48;
    local_3c = ((char)param_3 + (char)(param_3 / 10) * -10) * '\b';
    local_44 = local_3c + -0x80;
    local_3c = local_3c + -0x78;
    local_46 = param_2 + 4;
    local_3e = param_2 + 4;
    local_38 = local_48;
    local_36 = param_2 + 0xc;
    local_34 = local_44;
    local_30 = local_40;
    local_2e = param_2 + 0xc;
    local_2c = local_3c;
    FUN_800842a8(auStack_50,DAT_8009c85c,0x20);
    param_3 = param_3 / 10;
  } while (iVar2 < 3);
  return;
}

