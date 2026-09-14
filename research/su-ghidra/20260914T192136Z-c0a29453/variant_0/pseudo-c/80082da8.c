/* Analysis pseudo-C, not buildable source. */

void FUN_80082da8(int param_1,int param_2)

{
  byte bVar1;
  
  if (param_2 == 0) {
    bVar1 = *(byte *)(param_1 + 7) & 0xfd;
  }
  else {
    bVar1 = *(byte *)(param_1 + 7) | 2;
  }
  *(byte *)(param_1 + 7) = bVar1;
  return;
}

