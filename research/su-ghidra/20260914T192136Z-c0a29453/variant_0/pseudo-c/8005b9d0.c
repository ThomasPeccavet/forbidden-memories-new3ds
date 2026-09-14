/* Analysis pseudo-C, not buildable source. */

void FUN_8005b9d0(undefined4 param_1,byte param_2,undefined3 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined1 *puVar1;
  int iVar2;
  int *piVar3;
  uint local_res8;
  byte abStack_10 [7];
  undefined1 local_9;
  
  iVar2 = 7;
  puVar1 = &local_9;
  do {
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + -1;
  } while (-1 < iVar2);
  piVar3 = (int *)&stack0x00000014;
  while( true ) {
    iVar2 = *piVar3;
    if (iVar2 < 0) break;
    abStack_10[iVar2 >> 3] =
         abStack_10[iVar2 >> 3] | (byte)(1 << (iVar2 + (iVar2 >> 3) * -8 & 0x1fU));
    piVar3 = piVar3 + 1;
  }
  local_res8 = CONCAT13(param_2,param_3) & 0x7fffffff;
  FUN_8005bad0(param_1,param_2 & 0x80,local_res8,param_4,param_5,abStack_10);
  return;
}

