/* Analysis pseudo-C, not buildable source. */

void FUN_8008eac8(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  puVar1 = (undefined4 *)(*DAT_8009b20c + param_1 * 8);
  piVar2 = (int *)*puVar1;
  if (piVar2 == (int *)0x0) {
    *puVar1 = param_2;
  }
  else {
    for (; *piVar2 != 0; piVar2 = (int *)*piVar2) {
    }
    *piVar2 = (int)param_2;
  }
  *param_2 = 0;
  return;
}

