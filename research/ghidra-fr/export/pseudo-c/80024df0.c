/* Analysis pseudo-C, not buildable source. */

void FUN_80024df0(uint param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_80024a9c();
  if ((param_1 & 0x80) != 0) {
    param_1 = (param_1 & 0x7f) + 0xf;
  }
  iVar2 = FUN_80024cd8((int)*(short *)(&DAT_801a7adc)[param_1 * 7],
                       (int)*(short *)(&DAT_80091aa8 + param_1 * 4),
                       (int)*(short *)(&DAT_80091aaa + param_1 * 4));
  *piVar1 = iVar2;
  *(char *)(iVar2 + 0x6a) = (char)param_1;
  return;
}

