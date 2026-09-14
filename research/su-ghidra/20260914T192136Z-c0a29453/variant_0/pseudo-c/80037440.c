/* Analysis pseudo-C, not buildable source. */

void FUN_80037440(int param_1)

{
  if ((*(byte *)(param_1 + 0x51) & 0x80) == 0) {
    *(byte *)(param_1 + 0x51) = *(byte *)(param_1 + 0x51) | 0x80;
    FUN_80037354(param_1,3,0);
    *(undefined1 *)(param_1 + 0x51) = 0x82;
  }
  return;
}

