/* Analysis pseudo-C, not buildable source. */

void FUN_800399f0(int param_1)

{
  *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) | 0x800;
  do {
    FUN_800393b8(param_1);
  } while ((*(ushort *)(param_1 + 0x34) & 0x2000) == 0);
  return;
}

