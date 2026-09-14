/* Analysis pseudo-C, not buildable source. */

uint FUN_80082ce8(uint param_1,uint param_2,uint param_3,uint param_4)

{
  return (param_1 & 3) << 7 | (param_2 & 3) << 5 | (int)(param_4 & 0x100) >> 4 |
         (int)(param_3 & 0x3ff) >> 6 | (param_4 & 0x200) << 2;
}

