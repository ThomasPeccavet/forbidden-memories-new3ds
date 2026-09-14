/* Analysis pseudo-C, not buildable source. */

int FUN_8002a848(void)

{
  int iVar1;
  int iVar2;
  int unaff_gp;
  
  iVar1 = (((int)*(char *)(unaff_gp + 0x359) / 10) * 0x1000000 >> 0x18) * 200 +
          (((int)*(char *)(unaff_gp + 0x359) % 10) * 0x1000000 >> 0x18) * 10;
  if (9 < *(char *)(unaff_gp + 0x358)) {
    iVar1 = iVar1 + 100;
  }
  iVar2 = iVar1 + 1 + (((int)*(char *)(unaff_gp + 0x358) % 10) * 0x1000000 >> 0x18);
  iVar1 = 0;
  if (iVar2 < 0x2d3) {
    iVar1 = iVar2;
  }
  return iVar1;
}

