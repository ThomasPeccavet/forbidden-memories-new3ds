/* Analysis pseudo-C, not buildable source. */

void FUN_80085488(void)

{
  DAT_800ff430 = (&DAT_800ff3b8)[(short)DAT_800ff454];
  DAT_800ff432 = (&DAT_800ff3bc)[(short)DAT_800ff454];
  FUN_80080494();
  FUN_8007fbcc(1);
  DAT_800ff450 = DAT_800ff450 + 1;
  if (DAT_800ff450 == 0) {
    DAT_800ff450 = 1;
  }
  DAT_800ff454 = (ushort)(DAT_800ff454 == 0);
  FUN_800853c8();
  FUN_800852b8();
  return;
}

