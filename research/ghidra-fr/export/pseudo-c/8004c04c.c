/* Analysis pseudo-C, not buildable source. */

int FUN_8004c04c(uint param_1)

{
  int iVar1;
  
  do {
    iVar1 = FUN_8004bf30(&DAT_8009c304,*(int *)(DAT_8009c7d8 + 0x7dc) + param_1,4);
    if (iVar1 == 0) {
      return param_1 + 4;
    }
    param_1 = param_1 + 1;
  } while (param_1 <= *(uint *)(DAT_8009c7d8 + 0x7ec));
  return -1;
}

