/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80015d18(int *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 in_zero;
  undefined4 extraout_at;
  short local_10;
  short sStack_e;
  
  FUN_80085558(&DAT_800ff4d0);
  _DAT_1f8003e0 = (uint)*(ushort *)(*param_1 + 0x30);
  _DAT_1f8003e4 = CONCAT22(DAT_1f8003e4_2,*(undefined2 *)(*param_1 + 0x34));
  setCopReg(2,in_zero,_DAT_1f8003e0);
  setCopReg(2,extraout_at,_DAT_1f8003e4);
  copFunction(2,0x180001);
  uVar2 = getCopReg(2,0xe);
  local_10 = (short)uVar2;
  *(short *)(param_1 + 2) = local_10 + -0x1a;
  sStack_e = (short)((uint)uVar2 >> 0x10);
  bVar1 = DAT_8009c504 == '\0';
  *(short *)((int)param_1 + 10) = sStack_e + -0x1e;
  if (bVar1) {
    if ('\x0e' < (char)param_1[6]) {
      *(short *)((int)param_1 + 10) = sStack_e + -0x1d;
    }
  }
  else if ((char)param_1[6] < '\x0f') {
    *(short *)((int)param_1 + 10) = sStack_e + -0x1d;
  }
  FUN_800166a0(*param_1,DAT_8009c860,(int)(short)param_1[2],(int)*(short *)((int)param_1 + 10));
  FUN_80087838(0xa0,0x6c);
  return;
}

