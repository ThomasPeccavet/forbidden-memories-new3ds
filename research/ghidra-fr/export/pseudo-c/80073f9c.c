/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80073f9c(uint param_1)

{
  *(uint *)(DAT_80092d78 + 4) =
       *(uint *)(DAT_80092d78 + 4) & ~*(uint *)(&DAT_80092d80 + (param_1 & 0xffff) * 4);
  return 1;
}

