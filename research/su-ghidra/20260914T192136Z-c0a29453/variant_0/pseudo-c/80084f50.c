/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80084f50(ushort param_1,ushort param_2)

{
  DAT_800ff45c = (uint)param_1;
  DAT_800ff460 = (uint)param_2;
  if (DAT_800ff45c == 0) {
    trap(0x1c00);
  }
  if ((DAT_800ff45c == 0xffffffff) && (DAT_800ff460 == 0x20000)) {
    trap(0x1800);
  }
  DAT_800ff4f4 = 0;
  DAT_800ff4fc = 0;
  DAT_800ff50c = 0;
  DAT_800ff508 = 0;
  DAT_800ff504 = 0;
  DAT_800ff4f0 = 0x1000;
  DAT_800ff4f8 = 0x1000;
  DAT_800ff500 = CONCAT22(DAT_800ff500._2_2_,0x1000);
  DAT_800ff510 = 0x1000;
  DAT_800ff514 = 0;
  DAT_800ff51c = 0;
  DAT_800ff520 = DAT_800ff500;
  DAT_800ff524 = 0;
  DAT_800ff528 = 0;
  DAT_800ff52c = 0;
  DAT_800ff474 = 0;
  DAT_800ff47c = 0;
  DAT_800ff484 = 0;
  DAT_800ff488 = 0;
  DAT_800ff48c = 0;
  DAT_800ff480 = (uint)DAT_800ff500._2_2_ << 0x10;
  DAT_800ff478 = 0;
  DAT_800ff470 = 0;
  DAT_800ff490 = 0;
  DAT_800ff494 = 0;
  DAT_800ff498 = 0;
  DAT_800ff49c = 0;
  DAT_800ff4a0 = DAT_800ff480;
  DAT_800ff4a4 = 0;
  DAT_800ff4a8 = 0;
  DAT_800ff4ac = 0;
  DAT_800ff3c0 = 0;
  DAT_800ff3c2 = 0;
  DAT_800ff3c4 = 0;
  DAT_800ff3c6 = 0;
  DAT_800ff3ca = 0;
  DAT_800ff3c8 = 0;
  DAT_800ff44a = 0;
  _DAT_800ff518 =
       (uint)(ushort)((ulonglong)
                      ((longlong)(int)((DAT_800ff460 << 0xe) / DAT_800ff45c) * 0x55555556) >> 0x20);
  DAT_800ff448 = 0;
  DAT_800ff39b = 3;
  DAT_800ff39f = 2;
  DAT_800ff3ab = 3;
  DAT_800ff3af = 2;
  DAT_800ff450 = 1;
  DAT_800ff44c = param_1;
  DAT_800ff44e = param_2;
  return;
}

