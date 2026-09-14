/* Analysis pseudo-C, not buildable source. */

void FUN_8007132c(void)

{
  int iVar1;
  
  iVar1 = FUN_80070bd8();
  if (DAT_800f6f84 < 8) {
    *(int *)(&DAT_800f6f88 + (uint)DAT_800f6f84 * 4) = DAT_800f6f78;
    DAT_800f6f84 = DAT_800f6f84 + 1;
    DAT_800f6f78 = iVar1 + DAT_800f6f74;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

