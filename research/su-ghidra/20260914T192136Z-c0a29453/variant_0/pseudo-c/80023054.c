/* Analysis pseudo-C, not buildable source. */

void FUN_80023054(int *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  
  if (param_2 != 0) {
    iVar2 = *param_1;
    *(short *)(param_2 + 0x28) = *(short *)(param_2 + 0x30) - *(short *)(iVar2 + 0x30);
    *(short *)(param_2 + 0x2a) = *(short *)(param_2 + 0x32) - *(short *)(iVar2 + 0x32);
    bVar1 = *(byte *)((int)param_1 + 0x17);
    *(undefined1 *)(param_2 + 0x6c) = 1;
    *(code **)(param_2 + 0x24) = FUN_80022fa8;
    *(ushort *)(param_2 + 0x2c) = (ushort)bVar1;
  }
  return;
}

