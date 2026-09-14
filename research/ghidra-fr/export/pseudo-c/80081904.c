/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80081904(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_2 + -1;
  *DAT_80095ba0 = 0x4000000;
  if (param_2 != 0) {
    do {
      uVar1 = *param_1;
      param_1 = param_1 + 1;
      iVar2 = iVar2 + -1;
      *DAT_80095b9c = uVar1;
    } while (iVar2 != -1);
  }
  return 0;
}

