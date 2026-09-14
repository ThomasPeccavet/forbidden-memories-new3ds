/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_80090ea8(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_8009b30c;
  iVar2 = 0xf;
  puVar3 = param_1;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
    *puVar4 = uVar1;
    puVar4 = puVar4 + 1;
  } while (iVar2 != -1);
  puVar4 = &DAT_8009b34c;
  puVar3 = param_1 + 0x10;
  iVar2 = 0xf;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
    *puVar4 = uVar1;
    puVar4 = puVar4 + 1;
  } while (iVar2 != -1);
  FUN_80091198(&DAT_8009b308,0x20);
  FUN_80091198(&DAT_8009b38c,0x20);
  return param_1;
}

