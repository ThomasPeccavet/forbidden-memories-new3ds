/* Analysis pseudo-C, not buildable source. */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x80180000) */

void FUN_80169024(void)

{
  trap(0);
  trap(0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

