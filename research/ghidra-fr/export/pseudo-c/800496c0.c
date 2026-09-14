/* Analysis pseudo-C, not buildable source. */

void FUN_800496c0(ushort param_1,short param_2)

{
  int iVar1;
  undefined1 local_40 [2];
  ushort local_3e;
  int local_38;
  
  iVar1 = (int)((uint)param_1 << 0x10) >> 0x10;
  if (iVar1 < 0) {
    FUN_800494a0();
  }
  else {
    if ((uint)**(ushort **)(DAT_8009c7e0 + 0x1564) != (int)((uint)param_1 << 0x10) >> 0x14) {
      FUN_800495c8(iVar1,1);
    }
    local_40[0] = 0x48;
    local_38 = (int)param_2;
    local_3e = param_1;
    FUN_800460a4(local_40);
    iVar1 = DAT_8009c7e0;
    *(short *)(DAT_8009c7e0 + 0x1582) = param_2;
    *(undefined1 *)(iVar1 + 0x1584) = 0xff;
  }
  return;
}

