/* Analysis pseudo-C, not buildable source. */

bool FUN_80078b58(int *param_1,undefined4 *param_2)

{
  short sVar1;
  short *psVar2;
  
  psVar2 = (short *)(DAT_800f70e4 + DAT_800f70dc * 0x20);
  if (*psVar2 == 1) {
    DAT_800f70dc = 0;
    if (DAT_800f70d0 != 0) {
      *psVar2 = 0;
    }
    psVar2 = (short *)(DAT_800f70e4 + DAT_800f70dc * 0x20);
  }
  sVar1 = *psVar2;
  if (sVar1 == 2) {
    *psVar2 = 4;
    *param_1 = DAT_800f70e4 + DAT_800f70f0 * 0x20 + DAT_800f70dc * 0x7e0;
    *param_2 = psVar2;
  }
  return sVar1 != 2;
}

