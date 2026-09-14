/* Analysis pseudo-C, not buildable source. */

void FUN_8007c10c(byte param_1,byte *param_2)

{
  undefined4 *puVar1;
  
  if ((param_1 == 5) && ((*param_2 & 0x10) != 0)) {
    FUN_8007b02c(5);
  }
  if (param_1 == 4) {
    puVar1 = &DAT_800f7198;
  }
  else {
    if (param_1 < 5) {
      if (param_1 != 1) goto LAB_8007c1b0;
    }
    else if (param_1 != 5) goto LAB_8007c1b0;
    puVar1 = &DAT_800f7188;
  }
  *puVar1 = 1;
  *(byte *)(puVar1 + 1) = param_1;
  FUN_8007d304((int)puVar1 + 5,param_2);
LAB_8007c1b0:
  if (DAT_800f971c != (code *)0x0) {
    (*DAT_800f971c)(param_1,param_2);
  }
  return;
}

