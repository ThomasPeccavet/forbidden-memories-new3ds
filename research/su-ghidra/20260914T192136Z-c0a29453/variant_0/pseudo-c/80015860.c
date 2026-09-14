/* Analysis pseudo-C, not buildable source. */

void FUN_80015860(int param_1)

{
  int unaff_gp;
  
  if (param_1 == 0xffffff) {
    *(undefined1 *)(unaff_gp + 0x22d) = 1;
  }
  DAT_800eb248 = param_1;
  FUN_800157d4();
  DAT_800eb24e = DAT_800eb24e | 0x30;
  FUN_8001578c();
  return;
}

