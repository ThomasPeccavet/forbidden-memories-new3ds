/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008f328(void)

{
  int *in_v0;
  int *piVar1;
  
  piVar1 = &DAT_8008f314;
  do {
    if (*piVar1 != *in_v0) {
      return 0;
    }
    piVar1 = piVar1 + 1;
    in_v0 = in_v0 + 1;
  } while (piVar1 != (int *)0x8008f324);
  return 1;
}

