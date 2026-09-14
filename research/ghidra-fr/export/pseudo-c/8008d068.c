/* Analysis pseudo-C, not buildable source. */

void FUN_8008d068(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_8009b1a8 + 1;
  if (iVar3 < 4) {
    iVar2 = 3;
    puVar1 = &DAT_800ff73c + iVar3 * 4;
    DAT_8009b1a8 = iVar3;
    (&DAT_800ff770)[iVar3] = param_1;
    do {
      *puVar1 = 0;
      iVar2 = iVar2 + -1;
      puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
  }
  else {
    FUN_8008fa78(s_libmcrd__event_overflow_8001253c);
  }
  return;
}

