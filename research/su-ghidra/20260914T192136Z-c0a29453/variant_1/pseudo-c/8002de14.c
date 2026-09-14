/* Analysis pseudo-C, not buildable source. */

void seed_8002de14(void)

{
  int iVar1;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    DAT_8009c57a = 8000;
    DAT_8009c578 = 8000;
    FUN_80181050(&DAT_8009c578,&DAT_8009c57a,&DAT_8009c511);
    FUN_800361d8(0,0x25,0x20,0xc4,0x100,0x24,0x40);
    FUN_800399f0(&DAT_800f0850);
    FUN_800361d8(1,0x26,0x18,0x66,0x100,0x30,2);
    FUN_800399f0(&DAT_800f08b4);
    FUN_8004022c(0x72c0);
    FUN_8001591c();
  }
  iVar1 = FUN_80181408();
  if (iVar1 != 0) {
    FUN_80040258();
    FUN_80015a1c();
    FUN_80181f88();
    if (iVar1 == 1) {
      FUN_80024e84(0xffffffff,0xffffffff,0,0);
      DAT_8009c6fa = 8;
    }
    else {
      DAT_8009c60a = DAT_8009c60d;
    }
  }
  return;
}

