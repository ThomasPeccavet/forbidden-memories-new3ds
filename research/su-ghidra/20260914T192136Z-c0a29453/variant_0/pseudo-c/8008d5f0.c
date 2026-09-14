/* Analysis pseudo-C, not buildable source. */

int FUN_8008d5f0(void)

{
  int iVar1;
  
  do {
    iVar1 = DAT_800ff7a0 + DAT_800ff7a4 * 2 + DAT_800ff7a8 * 4 + DAT_800ff7ac * 8;
  } while (iVar1 == 0);
  FUN_80073dc8(DAT_800ff790);
  FUN_80073dc8(DAT_800ff794);
  FUN_80073dc8(DAT_800ff798);
  FUN_80073dc8(DAT_800ff79c);
  DAT_800ff7ac = 0;
  DAT_800ff7a8 = 0;
  DAT_800ff7a4 = 0;
  DAT_800ff7a0 = 0;
  return iVar1 >> 1;
}

