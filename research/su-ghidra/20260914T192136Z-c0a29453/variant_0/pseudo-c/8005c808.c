/* Analysis pseudo-C, not buildable source. */

void FUN_8005c808(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  
  if (param_2 < 1) {
    uVar2 = 0x23;
    if (param_2 < 0) {
      uVar2 = 0x3c;
    }
  }
  else {
    uVar2 = 0x3e;
  }
  (&DAT_800f4f8e)[param_1 * 0xe20] = uVar2;
  uVar3 = (uint)*(byte *)((int)&DAT_800f4f84 + param_1 * 0xe20 + 1);
  bVar1 = (&DAT_800f4f8e)[param_1 * 0xe20];
  iVar4 = uVar3 * 2;
  if (bVar1 == 0x3c) {
    iVar4 = uVar3 * -2;
  }
  else if (bVar1 < 0x3d) {
    iVar4 = 0;
    if (bVar1 != 0x23) {
      return;
    }
  }
  else if (bVar1 != 0x3e) {
    return;
  }
  FUN_8005d570(param_1,iVar4);
  return;
}

