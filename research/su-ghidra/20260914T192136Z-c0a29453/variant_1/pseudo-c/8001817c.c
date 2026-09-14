/* Analysis pseudo-C, not buildable source. */

uint FUN_8001817c(int param_1)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = *(byte *)(param_1 + 0x68);
  uVar2 = 1;
  if (bVar1 == 0x15) {
    uVar2 = 3;
    goto LAB_800181d0;
  }
  if (bVar1 < 0x16) {
    if (bVar1 != 0x14) goto LAB_800181d0;
  }
  else {
    if (bVar1 == 0x16) {
      uVar2 = 4;
      goto LAB_800181d0;
    }
    if (bVar1 != 0x17) goto LAB_800181d0;
  }
  uVar2 = 2;
LAB_800181d0:
  if (*(char *)(param_1 + 0x22) != '\0') {
    uVar2 = uVar2 | 0x80;
  }
  return uVar2;
}

