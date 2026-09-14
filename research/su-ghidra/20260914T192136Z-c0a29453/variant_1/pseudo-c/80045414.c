/* Analysis pseudo-C, not buildable source. */

void FUN_80045414(undefined2 param_1)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  
  *(undefined1 *)(DAT_8009c7e0 + 0x533) = 7;
  uVar3 = (undefined1)param_1;
  local_d = 0;
  if (*(char *)(DAT_8009c7e0 + 0x48) == '\0') {
    local_f = 0;
    local_e = uVar3;
  }
  else {
    local_e = 0;
    local_f = uVar3;
  }
  local_10 = uVar3;
  FUN_8007d358(&local_10);
  iVar1 = DAT_8009c7e0;
  *(undefined1 *)(DAT_8009c7e0 + 0x49) = uVar3;
  iVar2 = DAT_8009c7e0;
  *(undefined2 *)(iVar1 + 0x510) = param_1;
  *(undefined2 *)(iVar2 + 0x512) = 0;
  return;
}

