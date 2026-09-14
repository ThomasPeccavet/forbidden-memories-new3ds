/* Analysis pseudo-C, not buildable source. */

uint FUN_80081c90(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((*DAT_80095bac & 0x1000000) == 0) {
    DAT_80095bcc = FUN_80074a54(0);
    if (DAT_80095bc0 != DAT_80095bc4) {
      uVar1 = *DAT_80095bac;
      while ((uVar1 & 0x1000000) == 0) {
        if (((DAT_80095bc4 + 1 & 0x3f) == DAT_80095bc0) && (DAT_80095aa4 == (code *)0x0)) {
          FUN_80074938(2,0);
        }
        uVar1 = *DAT_80095ba0;
        while ((uVar1 & 0x4000000) == 0) {
          uVar1 = *DAT_80095ba0;
        }
        (**(code **)(&DAT_800fdb88 + DAT_80095bc4 * 0x60))
                  (*(undefined4 *)(&DAT_800fdb8c + DAT_80095bc4 * 0x60),
                   *(undefined4 *)(&DAT_800fdb90 + DAT_80095bc4 * 0x60));
        DAT_80095bc4 = DAT_80095bc4 + 1 & 0x3f;
        if (DAT_80095bc0 == DAT_80095bc4) break;
        uVar1 = *DAT_80095bac;
      }
    }
    FUN_80074a54(DAT_80095bcc);
    if ((((DAT_80095bc0 == DAT_80095bc4) && ((*DAT_80095bac & 0x1000000) == 0)) &&
        (DAT_80095aa0 != 0)) && (DAT_80095aa4 != (code *)0x0)) {
      DAT_80095aa0 = 0;
      (*DAT_80095aa4)();
    }
    uVar1 = DAT_80095bc0 - DAT_80095bc4 & 0x3f;
  }
  return uVar1;
}

