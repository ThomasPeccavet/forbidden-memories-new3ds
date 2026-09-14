/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8002f128(void)

{
  undefined2 uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = FUN_8002e650();
  if (iVar4 == 0) {
    DAT_8009c6d0 = -1;
    uVar1 = *DAT_8009c624;
    _DAT_8009c620 = DAT_8009c624[1];
    DAT_8009c624 = DAT_8009c624 + 2;
    uVar5 = FUN_80036184(0,uVar1,0x10,0xb0,0x120,0x40);
  }
  else {
    if ((DAT_8009c610 & 0x80) != 0) {
      iVar4 = FUN_8003fa30();
      if (iVar4 == 0) {
        return;
      }
      DAT_8009c610 = DAT_8009c610 & 0xff7f;
      DAT_8009c6c1 = 4;
      DAT_8009c6c8 = 0;
      DAT_8009c6d0 = 0;
      return;
    }
    FUN_80039770(0);
    iVar4 = DAT_800f09a4;
    uVar2 = DAT_8009c610;
    if ((DAT_8009c610 & 0x4000) == 0) {
      if ((DAT_800f0884 & 0x2000) == 0) {
        return;
      }
      iVar4 = FUN_800372e0();
      if (iVar4 != 0) {
        return;
      }
      DAT_8009c610 = DAT_8009c610 | 0x4000;
      iVar4 = FUN_8002f0f0();
      if (iVar4 == 0) {
        DAT_8009c610 = DAT_8009c610 | 0x200;
        FUN_80040204(0x2a);
        return;
      }
      iVar4 = FUN_80036184(3,0x11,0xffffff70,0x38,0x78,0x40);
      FUN_8002e60c(iVar4);
      *(ushort *)(iVar4 + 0x34) = *(ushort *)(iVar4 + 0x34) | 0x48;
      do {
        FUN_80039770();
      } while (*(int *)(iVar4 + 0x30) == 0);
      FUN_800434a8(*(undefined4 *)(iVar4 + 0x28));
      *(undefined2 *)(*(int *)(iVar4 + 0x28) + 0x60) = 0xfc00;
      DAT_8009c610 = DAT_8009c610 | 0x6000;
      return;
    }
    if ((DAT_8009c610 & 0x400) != 0) {
      if ((DAT_8009c610 & 0x800) == 0) {
        DAT_8009c610 = DAT_8009c610 | 0x800;
        iVar4 = FUN_80036184(2,0x12,0x90,0x70,0x18,0x20);
        FUN_8002e60c(iVar4);
        *(ushort *)(iVar4 + 0x34) = *(ushort *)(iVar4 + 0x34) | 0x40;
        do {
          FUN_80039770();
        } while (*(int *)(iVar4 + 0x30) == 0);
      }
      if ((DAT_800f094c & 0x2000) == 0) {
        return;
      }
      DAT_8009c610 = DAT_8009c610 & 0xf3ff;
      FUN_800360d8();
      if (DAT_8009c6d0 != '\0') {
        DAT_8009c60c = 1;
        DAT_8009c60e = 5;
        DAT_8009c60a = 8;
      }
      DAT_8009c6c1 = 4;
      DAT_8009c6d0 = 2;
      return;
    }
    if ((DAT_8009c610 & 0x200) == 0) {
      if ((DAT_8009c610 & 0x1000) == 0) {
        if ((DAT_8009c610 & 0x2000) == 0) {
          iVar4 = FUN_80036f7c(&DAT_800f097c);
          if (iVar4 != 0) {
            return;
          }
          if ((DAT_8009c72c & 0xc0) == 0) {
            return;
          }
          DAT_801d07dc = _DAT_8009c620;
          if (DAT_8009c6d0 == '\x01') {
            FUN_80040204(7);
            FUN_80034190();
            DAT_8009c638 = DAT_8009c620;
            DAT_8009c60d = 2;
            return;
          }
          if (DAT_8009c6d0 < '\x02') {
            if (DAT_8009c6d0 != '\0') {
              DAT_801d07dc = _DAT_8009c620;
              return;
            }
            FUN_80040204(7);
            DAT_801d07dc = _DAT_8009c620;
            FUN_8003fba0();
            DAT_8009c610 = DAT_8009c610 | 0x80;
            return;
          }
          if (DAT_8009c6d0 == '\x02') {
            FUN_80040204(7);
            DAT_8009c610 = DAT_8009c610 | 0x400;
            return;
          }
          if (DAT_8009c6d0 != '\x03') {
            DAT_801d07dc = _DAT_8009c620;
            return;
          }
          FUN_80040204(8);
          DAT_8009c610 = DAT_8009c610 | 0x1000;
          return;
        }
        sVar3 = *(short *)(DAT_800f09a4 + 0x60) + 0x40;
        *(short *)(DAT_800f09a4 + 0x60) = sVar3;
        if (-1 < sVar3) {
          *(undefined2 *)(iVar4 + 0x30) = 0x10;
          *(undefined2 *)(iVar4 + 0x32) = 0x38;
          DAT_8009c610 = uVar2 & 0xdfff;
          FUN_80039910(&DAT_800f097c,(int)*(short *)(iVar4 + 0x30),(int)*(short *)(iVar4 + 0x32));
          return;
        }
        uVar5 = 0x10;
      }
      else {
        if ((DAT_8009c610 & 0x800) == 0) {
          DAT_8009c610 = DAT_8009c610 | 0x800;
          FUN_800434a8(DAT_800f09a4);
          *(undefined2 *)(DAT_800f09a4 + 0x60) = 0x400;
        }
        sVar3 = *(short *)(iVar4 + 0x60) + -0x40;
        *(short *)(iVar4 + 0x60) = sVar3;
        if (sVar3 < 1) {
          FUN_800360d8(&DAT_800f097c);
          DAT_8009c610 = 0;
          return;
        }
        uVar5 = 0xffffff70;
      }
      FUN_80043560(iVar4,uVar5,0x38);
      FUN_80039910(&DAT_800f097c,(int)*(short *)(iVar4 + 0x30),(int)*(short *)(iVar4 + 0x32));
      return;
    }
    if ((DAT_8009c610 & 0x800) != 0) {
      if ((DAT_800f0884 & 0x10) != 0) {
        return;
      }
      FUN_80040204(8);
      DAT_8009c60a = 8;
      DAT_8009c60c = 1;
      DAT_8009c60e = 5;
      return;
    }
    DAT_8009c610 = DAT_8009c610 | 0x800;
    uVar5 = FUN_800361d8(0,0x1c,0x10,0xb0,0x120,0x30,0x1010);
  }
  FUN_8002e60c(uVar5);
  return;
}

