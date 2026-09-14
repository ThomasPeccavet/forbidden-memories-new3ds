/* Analysis pseudo-C, not buildable source. */

bool FUN_80042c90(int param_1)

{
  if (*(code **)(param_1 + 0x24) != (code *)0x0) {
    (**(code **)(param_1 + 0x24))();
  }
  return (*(ushort *)(param_1 + 8) & 0xc0) == 0xc0;
}

