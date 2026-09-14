/* Analysis pseudo-C, not buildable source. */

undefined2 FUN_80073f34(uint param_1)

{
  undefined2 uVar1;
  
  if ((param_1 & 0xffff) < 3) {
    uVar1 = *(undefined2 *)((param_1 & 0xffff) * 0x10 + DAT_80092d7c);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

