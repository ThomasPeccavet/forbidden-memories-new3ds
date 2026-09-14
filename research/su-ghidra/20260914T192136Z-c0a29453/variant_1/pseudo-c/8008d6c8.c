/* Analysis pseudo-C, not buildable source. */

int FUN_8008d6c8(void)

{
  int iVar1;
  
  do {
    iVar1 = DAT_800ff7b0 + DAT_800ff7b4 * 2 + DAT_800ff7b8 * 4 + DAT_800ff7bc * 8;
  } while (iVar1 == 0);
  FUN_80073dc8(DAT_800ff780);
  FUN_80073dc8(DAT_800ff784);
  FUN_80073dc8(DAT_800ff788);
  FUN_80073dc8(DAT_800ff78c);
  DAT_800ff7bc = 0;
  DAT_800ff7b8 = 0;
  DAT_800ff7b4 = 0;
  DAT_800ff7b0 = 0;
  return iVar1 >> 1;
}

