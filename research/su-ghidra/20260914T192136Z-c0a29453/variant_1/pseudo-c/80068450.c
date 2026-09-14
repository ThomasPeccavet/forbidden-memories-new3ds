/* Analysis pseudo-C, not buildable source. */

uint FUN_80068450(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  byte local_10;
  byte local_f;
  byte local_e;
  
  FUN_80067f9c(&local_10,param_1,param_2,param_3,0x1f);
  return local_10 & 0x1f | (local_f & 0x1f) << 5 | (local_e & 0x1f) << 10;
}

