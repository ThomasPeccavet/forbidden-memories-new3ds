/* Analysis pseudo-C, not buildable source. */

void FUN_80014478(void)

{
  int iVar1;
  
  if ((((DAT_8009c460 & 0x1000) != 0) && ((DAT_8009c460 & 0x800) == 0)) &&
     (iVar1 = FUN_8007b78c(0x10,0,FUN_800142ac,0), 0 < iVar1)) {
    DAT_8009c460 = DAT_8009c460 | 0x800;
  }
  if ((DAT_8009c460 & 0x400) != 0) {
    return;
  }
  if ((DAT_8009c460 & 0x80000) == 0) {
    if (DAT_800eb1fe == '\x05') {
      if (DAT_800eb1ff == '\0') {
        FUN_8007e36c();
        FUN_8007edf8(0);
        iVar1 = FUN_8007b78c(9,0,FUN_800140c4,0xffffffff);
        if (iVar1 < 1) {
          return;
        }
        DAT_8009c460 = DAT_8009c460 | 0x400;
        return;
      }
      if (DAT_800eb1ff != '\x01') {
        return;
      }
      FUN_8007e36c();
      FUN_8007edf8(0);
    }
    else if ((DAT_8009c460 & 0x80) == 0) {
      FUN_8007eb98(DAT_800eb1dc,&DAT_8009c4b4);
      iVar1 = DAT_800eb1f8;
      if ((DAT_8009c460 & 0x100000) == 0) {
        if ((DAT_8009c460 & 0x800000) == 0) {
          DAT_8009c460 = DAT_8009c460 | 0x800000;
          if (DAT_800eb1d8 != (code *)0x0) {
            DAT_800eb1f8 = DAT_800eb1f8 + 1;
            (*DAT_800eb1d8)(&DAT_800eb1b8,iVar1);
          }
          DAT_800eb1e0 = DAT_800eb1d4;
          return;
        }
        if ((DAT_8009c460 & 0x400000) != 0) {
          iVar1 = FUN_800777d8(0);
          if (iVar1 == 0) {
            return;
          }
          DAT_8009c460 = DAT_8009c460 & 0xffbfffff;
        }
        if (-1 < (int)DAT_8009c460) {
          iVar1 = FUN_8007ba00(0xa0,&DAT_8009c4b4,6,FUN_80013fbc,0xffffffff);
          if (iVar1 == 0) {
            return;
          }
          DAT_8009c460 = DAT_8009c460 | 0x400;
        }
        DAT_8009c460 = DAT_8009c460 | 0x180;
        return;
      }
      if (-1 < (int)DAT_8009c460) {
        iVar1 = FUN_8007ba00(0xa0,&DAT_8009c4b4,0x15,FUN_80014050,0xffffffff);
        if (iVar1 < 1) {
          return;
        }
        DAT_8009c460 = DAT_8009c460 | 0x480;
        return;
      }
    }
    else if ((DAT_8009c460 & 0x100) != 0) {
      return;
    }
    goto LAB_8001462c;
  }
  if ((DAT_8009c47c & 0x8000) == 0) {
    if ((DAT_8009c47c & 3) != 0) {
      if ((DAT_8009c47c & 0x2000) == 0) {
        DAT_8009c464 = 0;
      }
      if ((DAT_8009c47c & 2) == 0) {
        DAT_800eb1e8 = 0;
        DAT_8009c47c = DAT_8009c47c | 0x8000;
      }
      else {
        DAT_8009c47c = DAT_8009c47c & 0xfffe | 0x8000;
      }
      goto LAB_80014580;
    }
LAB_80014628:
    DAT_8009c47c = 0;
LAB_8001462c:
    FUN_800143d4();
    return;
  }
LAB_80014580:
  switch(DAT_8009c464) {
  case 0:
    DAT_8009c47c = DAT_8009c47c | 0x2000;
    DAT_8009c464 = 1;
  case 1:
    iVar1 = FUN_8007b78c(9,0,FUN_8001413c,0xffffffff);
    if (0 < iVar1) {
      DAT_8009c460 = DAT_8009c460 | 0x400;
LAB_80014760:
      if (DAT_8009c488 != (code *)0x0) {
        (*DAT_8009c488)();
      }
    }
    break;
  case 2:
    if ((DAT_8009c47c & 1) == 0) goto LAB_80014628;
    DAT_8009c464 = 3;
    DAT_8009c47c = DAT_8009c47c & 0xdfff;
  case 3:
    DAT_8009c47c = DAT_8009c47c | 0x1000;
    DAT_8009c469 = DAT_800eb1f0;
    DAT_8009c468 = DAT_800eb1f1;
    iVar1 = FUN_8007b78c(0xd,&DAT_8009c468,FUN_800141b0,0xffffffff);
    if (0 < iVar1) {
      DAT_8009c460 = DAT_8009c460 | 0x400;
    }
    break;
  case 4:
    FUN_8007eb98(DAT_800eb1dc,&DAT_8009c4b4);
    iVar1 = FUN_8007ba00(0x4a,&DAT_8009c4b4,0x1b,FUN_80014224,0xffffffff);
    if (iVar1 < 1) {
      return;
    }
    DAT_8009c460 = DAT_8009c460 | 0x400;
    return;
  case 5:
    DAT_8009c464 = 6;
    DAT_8009c498 = 600;
    DAT_8009c47c = DAT_8009c47c & 0xefff | 0x4000;
    if (DAT_8009c49c != (code *)0x0) {
      (*DAT_8009c49c)();
    }
  case 6:
    DAT_8009c498 = DAT_8009c498 - 1;
    if ((0 < (int)((uint)DAT_8009c498 << 0x10)) && (DAT_800eb1e8 < DAT_800eb1ec)) {
      return;
    }
    DAT_8009c47c = DAT_8009c47c & 0x3ffc | 2;
    goto LAB_80014760;
  default:
    break;
  }
  return;
}

