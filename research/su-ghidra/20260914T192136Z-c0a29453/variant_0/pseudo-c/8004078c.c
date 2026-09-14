/* Analysis pseudo-C, not buildable source. */

int FUN_8004078c(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                undefined4 param_5,uint param_6)

{
  ushort uVar1;
  
  *(undefined1 *)(param_1 + 0x67) = param_2;
  *(undefined1 *)(param_1 + 0x68) = param_3;
  *(undefined1 *)(param_1 + 0x69) = param_4;
  *(char *)(param_1 + 0x66) = (char)param_5;
  *(char *)(param_1 + 0x5e) = (char)((uint)param_5 >> 0x10);
  *(ushort *)(param_1 + 0x40) = ((ushort)param_6 & 0xf0) + 0x280;
  *(char *)(param_1 + 0x5f) = (char)((uint)param_5 >> 8);
  *(ushort *)(param_1 + 0x42) =
       (short)((int)(param_6 & 0x300) >> 4) + 0xd0 + ((ushort)param_6 & 0xf);
  uVar1 = *(ushort *)(param_1 + 8) & 0xffdf;
  *(ushort *)(param_1 + 8) = uVar1;
  if ((param_6 & 0x8000) != 0) {
    *(ushort *)(param_1 + 8) = uVar1 | 0x20;
  }
  return param_1;
}

