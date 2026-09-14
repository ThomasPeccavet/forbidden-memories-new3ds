/* Analysis pseudo-C, not buildable source. */

uint FUN_800770d8(int param_1,int param_2)

{
  return (uint)*(ushort *)(param_1 * 2 + DAT_80093fb8) |
         (*(ushort *)(param_2 * 2 + DAT_80093fb8) & 0xff) << 0x10;
}

