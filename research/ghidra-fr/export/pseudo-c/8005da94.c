/* Analysis pseudo-C, not buildable source. */

uint FUN_8005da94(ushort param_1,uint param_2,ushort *param_3)

{
  short sVar1;
  
  sVar1 = (param_1 & 1) * 0x100;
  param_3[2] = (param_3[2] - 0x280) + sVar1;
  if ((short)param_3[9] < 0x100) {
    if (param_3[9] == 8) {
      param_3[9] = (param_1 & 1) + 0xf2;
    }
  }
  else {
    param_3[8] = (param_3[8] - 0x280) + sVar1;
  }
  return ((*param_3 & 3) << 7 | (param_2 & 3) << 5 | (int)((param_3[3] & 0x100) << 0x10) >> 0x14 |
          (param_3[2] & 0x3ff) >> 6 | (param_3[3] & 0x200) << 2) << 0x10 |
         (param_3[9] & 0x3ff) << 6 | param_3[8] >> 4 & 0x3f;
}

