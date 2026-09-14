/* Analysis pseudo-C, not buildable source. */

bool FUN_80073f6c(uint param_1)

{
  *(uint *)(DAT_80092d78 + 4) =
       *(uint *)(DAT_80092d78 + 4) | *(uint *)(&DAT_80092d80 + (param_1 & 0xffff) * 4);
  return (param_1 & 0xffff) < 3;
}

