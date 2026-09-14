/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_8007ed28(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    param_1 = (undefined4 *)FUN_8007c4bc();
  }
  else {
    puVar1 = (undefined4 *)FUN_8007c4bc();
    *param_1 = *puVar1;
  }
  return param_1;
}

