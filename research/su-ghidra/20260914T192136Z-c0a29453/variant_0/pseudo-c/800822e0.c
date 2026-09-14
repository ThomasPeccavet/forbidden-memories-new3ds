/* Analysis pseudo-C, not buildable source. */

undefined8 FUN_800822e0(uint param_1)

{
  uint *puVar1;
  undefined4 uVar2;
  uint *puVar3;
  
  *DAT_80095ba0 = 0x10000007;
  puVar1 = DAT_80095ba0;
  puVar3 = (uint *)0xe1000000;
  if ((*DAT_80095b9c & 0xffffff) == 2) {
    if ((param_1 & 8) == 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 2;
      *DAT_80095ba0 = 0x9000001;
      puVar3 = puVar1;
    }
  }
  else {
    *DAT_80095b9c = *DAT_80095ba0 & 0x3fff | 0xe1001000;
    uVar2 = 0;
    puVar3 = (uint *)*DAT_80095b9c;
  }
  return CONCAT44(puVar3,uVar2);
}

