/* Analysis pseudo-C, not buildable source. */

byte FUN_8007fab8(uint param_1)

{
  byte bVar1;
  
  bVar1 = DAT_80095a99;
  if (1 < DAT_80095a9a) {
    (*(code *)PTR_FUN_80095a94)(s_SetGrapQue__d_____800120f4,param_1);
  }
  if (param_1 != DAT_80095a99) {
    (**(code **)(PTR_PTR_80095a90 + 0x34))(1);
    DAT_80095a99 = (byte)param_1;
    FUN_80074938(2,0);
  }
  return bVar1;
}

