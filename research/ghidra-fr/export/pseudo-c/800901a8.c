/* Analysis pseudo-C, not buildable source. */

void FUN_800901a8(byte param_1)

{
  if (param_1 == 9) {
    do {
      FUN_800901a8(0x20);
    } while ((DAT_8009b248 & 7) != 0);
  }
  else {
    if (param_1 == 10) {
      FUN_800901a8(0xd);
      DAT_8009b248 = 0;
    }
    else if (((int)(char)(&DAT_8009b279)[param_1] & 0x97U) != 0) {
      DAT_8009b248 = DAT_8009b248 + 1;
    }
    if (0x1f < DAT_8009b24c) {
      FUN_80073e48(1,&DAT_800ffc10);
      DAT_8009b24c = 0;
    }
    (&DAT_800ffc10)[DAT_8009b24c] = param_1;
    DAT_8009b24c = DAT_8009b24c + 1;
  }
  return;
}

