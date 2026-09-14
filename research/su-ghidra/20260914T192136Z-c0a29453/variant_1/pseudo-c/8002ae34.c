/* Analysis pseudo-C, not buildable source. */

void FUN_8002ae34(byte *param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined4 uVar10;
  byte *pbVar11;
  short sVar12;
  int iVar13;
  
  if ((*param_1 & 0x80) == 0) {
    *param_1 = *param_1 | 0x80;
    param_1[1] = 0;
    param_1[3] = 0;
    param_1[4] = 1;
    FUN_8005622c();
    FUN_80056540();
    DAT_800f11e0 = 0x334;
    DAT_800f11e2 = 0x400;
    DAT_800f11e4 = 0xc4;
    DAT_800f11ec = 0;
    DAT_800f1208 = 0;
    DAT_800f120c = 0;
    DAT_800f11ee = 300;
    FUN_80085748();
    DAT_800f11fc = 0;
    DAT_800f11e6 = 0;
    DAT_800f1200 = 0;
    DAT_800f11e8 = 0;
    DAT_800f1204 = 0;
    DAT_800f11ea = 0;
    FUN_80013448();
    FUN_800292dc(0,*(undefined2 *)(param_1 + 6));
    FUN_80015ba0();
    DAT_800eb24f = 6;
    param_1[0x50] = 0;
    param_1[0x51] = 0;
    param_1[0x52] = 0;
    param_1[0x53] = 0;
    return;
  }
  FUN_80039770();
  if (((param_1[4] & 0xf) != 0) && ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0)) {
    if (param_1[4] == 1) {
      param_1[4] = 0;
      if (((int)(&DAT_801d4244)[*(ushort *)(param_1 + 6) - 1] >> 0x1a & 0x1fU) < 0x14) {
        FUN_8005967c(0,*(ushort *)(param_1 + 6) - 1,0,0,0,0,4);
        param_1[0x20] = 0x2c;
        param_1[0x21] = 1;
        param_1[0x22] = 0;
        param_1[0x23] = 0;
        param_1[4] = 2;
      }
    }
    else {
      FUN_800599a0(0);
      iVar13 = FUN_8005bee0(0);
      if (iVar13 == 1) {
        param_1[4] = 0;
        uVar10 = FUN_80040350();
        iVar13 = FUN_800403d0(uVar10,2);
        FUN_80040800(iVar13,0x130,0xdd,3,0,2,0xb,0x20c);
        *(ushort *)(iVar13 + 8) = *(ushort *)(iVar13 + 8) | 0x28;
        FUN_80042c48(iVar13);
        FUN_80042c1c(iVar13,10);
        *(int *)(param_1 + 0x50) = iVar13;
      }
    }
  }
  bVar2 = param_1[3];
  if ((bVar2 & 0xf) == 1) {
    iVar13 = *(int *)(param_1 + 0x4c);
    if ((bVar2 & 0x80) == 0) {
      param_1[3] = bVar2 | 0x80;
      *(undefined2 *)(iVar13 + 0x30) = 0x148;
      *(undefined2 *)(iVar13 + 0x32) = 6;
      FUN_800434a8(iVar13);
      *(undefined2 *)(iVar13 + 0x60) = 0xfc00;
    }
    sVar3 = *(short *)(iVar13 + 0x60) + 0x33;
    *(short *)(iVar13 + 0x60) = sVar3;
    uVar4 = 0x98;
    if (-1 < sVar3) goto LAB_8002b110;
    uVar10 = 0x98;
LAB_8002b128:
    FUN_80043560(iVar13,uVar10,6);
LAB_8002b130:
    FUN_80039910(&DAT_800f0850,(int)*(short *)(iVar13 + 0x30),(int)*(short *)(iVar13 + 0x32));
  }
  else if ((bVar2 & 0xf) == 2) {
    iVar13 = *(int *)(param_1 + 0x4c);
    if ((bVar2 & 0x80) == 0) {
      param_1[3] = bVar2 | 0x80;
      FUN_800434a8(iVar13);
      *(undefined2 *)(iVar13 + 0x60) = 0x400;
    }
    sVar3 = *(short *)(iVar13 + 0x60) + -0x33;
    *(short *)(iVar13 + 0x60) = sVar3;
    uVar10 = 0x148;
    if (0 < sVar3) goto LAB_8002b128;
    uVar4 = 0x148;
LAB_8002b110:
    *(undefined2 *)(iVar13 + 0x30) = uVar4;
    *(undefined2 *)(iVar13 + 0x32) = 6;
    param_1[3] = 0;
    goto LAB_8002b130;
  }
  iVar13 = DAT_800eb470;
  switch(param_1[1] & 0x1f) {
  case 0:
    param_1[(uint)*(ushort *)(param_1 + 6) * 4 + 0x56] =
         param_1[(uint)*(ushort *)(param_1 + 6) * 4 + 0x56] & 0x7f;
    iVar13 = FUN_80029354(0,0xffffffff,0xffffffff);
    *(ushort *)(iVar13 + 8) = *(ushort *)(iVar13 + 8) | 4;
    *(uint *)(iVar13 + 4) = *(uint *)(iVar13 + 4) & 0xf7ffffff;
    *(short *)(iVar13 + 0x30) =
         (*(short *)(param_1 + 0x12) - DAT_8009c4c0) - *(short *)(iVar13 + 0x48);
    sVar12 = DAT_8009c4c2;
    sVar3 = *(short *)(param_1 + 0x14);
    *(undefined2 *)(iVar13 + 0x46) = 0;
    *(undefined2 *)(iVar13 + 0x44) = 0;
    *(short *)(iVar13 + 0x32) = (sVar3 - sVar12) - *(short *)(iVar13 + 0x4a);
    FUN_800434a8(iVar13);
    *(undefined2 *)(iVar13 + 0x60) = 0;
    FUN_80040204(0x32);
    *(uint *)(DAT_800eb474 + 4) = *(uint *)(DAT_800eb474 + 4) | 0x80000000;
    uVar10 = FUN_80040350();
    iVar13 = FUN_800403d0(uVar10,2);
    FUN_80040800(iVar13,0x148,6,0,2,0,0x1b,0x107);
    *(undefined1 *)(iVar13 + 0x5f) = 0x80;
    *(undefined2 *)(iVar13 + 0x60) = 0xfc00;
    *(ushort *)(iVar13 + 8) = *(ushort *)(iVar13 + 8) | 8;
    FUN_80042c48(iVar13);
    FUN_80042c1c(iVar13,4);
    *(int *)(param_1 + 0x4c) = iVar13;
    DAT_8009c6b8 = *(ushort *)(param_1 + 6);
    param_1[3] = 1;
    uVar10 = 3;
    if (0x13 < (*(int *)(&DAT_801d4240 + ((int)((uint)DAT_8009c6b8 << 0x10) >> 0xe)) >> 0x1a & 0x1fU
               )) {
      uVar10 = 4;
    }
    iVar13 = FUN_80036184(0,uVar10,0x98,6,0xa0,0xd0);
    *(undefined1 *)(iVar13 + 0x53) = 1;
    *(undefined1 *)(iVar13 + 0x59) = 4;
    param_1[1] = 1;
    break;
  case 1:
    FUN_8002ad44(DAT_800eb470,0xffffffff);
    if ((*(uint *)(iVar13 + 4) & 0x8000000) == 0) {
      sVar12 = *(short *)(iVar13 + 0x60) + 0x66;
      *(char *)(iVar13 + 0x22) = *(char *)(iVar13 + 0x22) + '\f';
      sVar3 = *(short *)(iVar13 + 0x44) + 0xcc;
      *(short *)(iVar13 + 0x44) = sVar3;
      *(short *)(iVar13 + 0x46) = sVar3;
      *(short *)(iVar13 + 0x60) = sVar12;
      *(char *)(iVar13 + 0x21) = *(char *)(iVar13 + 0x21) + '\x06';
      FUN_800434bc(iVar13,2,0,(int)sVar12);
      if (0x7ff < *(short *)(iVar13 + 0x60)) {
        *(undefined4 *)(iVar13 + 0x20) = 0x8000;
        *(undefined4 *)(iVar13 + 0x30) = 2;
        *(undefined4 *)(iVar13 + 0x44) = 0x10001000;
        *(uint *)(DAT_800eb474 + 4) = *(uint *)(DAT_800eb474 + 4) & 0x7fffffff;
        *(uint *)(iVar13 + 4) = *(uint *)(iVar13 + 4) | 0x8000000;
      }
      if ((*(uint *)(iVar13 + 4) & 0x8000000) == 0) {
        return;
      }
    }
    if (param_1[3] == 0) {
      param_1[1] = 2;
    }
    break;
  case 2:
    if (param_1[4] == 1) {
      return;
    }
    if ((DAT_800eb24e & 0x80) != 0) {
      return;
    }
    DAT_8009c8a4 = (undefined1 *)0x0;
    iVar13 = 0;
    pbVar11 = param_1;
    do {
      iVar13 = iVar13 + 1;
      *(ushort *)(*(int *)(pbVar11 + 0x24) + 8) = *(ushort *)(*(int *)(pbVar11 + 0x24) + 8) & 0xffbf
      ;
      pbVar11 = pbVar11 + 4;
    } while (iVar13 < 9);
    *(ushort *)(DAT_800f09a4 + 8) = *(ushort *)(DAT_800f09a4 + 8) & 0xffbf;
    param_1[1] = 3;
    FUN_80040204(0x31);
  case 3:
    iVar13 = DAT_800eb470;
    cVar1 = *(char *)(DAT_800eb470 + 0x21) + '\b';
    *(char *)(DAT_800eb470 + 0x21) = cVar1;
    if (cVar1 == '\0') {
      *(ushort *)(iVar13 + 8) = *(ushort *)(iVar13 + 8) & 0xfffb;
LAB_8002b94c:
      param_1[1] = 5;
    }
    break;
  case 4:
    piVar5 = (int *)FUN_8005c2c8(0,2);
    iVar9 = (int)DAT_800f11e0;
    iVar13 = FUN_800866f8((int)DAT_800f11e4);
    iVar13 = -iVar9 * iVar13;
    if (iVar13 < 0) {
      iVar13 = iVar13 + 0xfff;
    }
    iVar6 = FUN_80086628((int)DAT_800f11e4);
    iVar6 = -iVar9 * iVar6;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xfff;
    }
    iVar9 = FUN_80086628(DAT_800f11e2 + 0x800);
    iVar9 = (iVar13 >> 0xc) * iVar9;
    if (iVar9 < 0) {
      iVar9 = iVar9 + 0xfff;
    }
    iVar7 = FUN_800866f8(DAT_800f11e2 + 0x800);
    iVar7 = (iVar13 >> 0xc) * iVar7;
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0xfff;
    }
    *piVar5 = iVar7 >> 0xc;
    piVar5[1] = iVar6 >> 0xc;
    piVar5[2] = iVar9 >> 0xc;
    iVar13 = DAT_800eb470;
    if ((param_1[1] & 0x80) == 0) {
      param_1[1] = param_1[1] | 0x80;
      param_1[2] = 0;
      DAT_8009c424 = 1;
      DAT_8009c8a0 = FUN_80029acc;
      param_1[0x10] = 0;
      param_1[0x11] = 0;
      if ((*param_1 & 0x40) == 0) {
        *param_1 = *param_1 | 0x40;
        puVar8 = (undefined4 *)FUN_8005c2c8(0,0);
        puVar8[1] = 0xfffff000;
        *puVar8 = 0;
        puVar8[2] = 0;
        puVar8[3] = 0xffffff;
        puVar8[4] = 0;
        puVar8[5] = 0x1000;
        puVar8[6] = 0;
        puVar8[7] = 0x404040;
        puVar8[0xb] = 0xc0c0c0;
        FUN_8005c6d0(0,0x400,0x400,0x400);
        FUN_8005c0b8(0,0x80181000);
        DAT_800f11fc = (int)sRam80181000;
        DAT_800f1200 = (int)sRam80181002;
        DAT_800f1204 = (int)sRam80181004;
        DAT_800f11e0 = FUN_8004f1c8(0,0x334);
        FUN_8005cbb0(0,1);
        FUN_8005cbe8(0);
      }
      FUN_8005ac78(0,0,1);
      FUN_8005c8d0(0,1,0);
      param_1[0x20] = 0x2c;
      param_1[0x21] = 1;
      param_1[0x22] = 0;
      param_1[0x23] = 0;
      param_1[3] = 2;
      iVar13 = DAT_800eb470;
      *(ushort *)(DAT_800eb470 + 8) = *(ushort *)(DAT_800eb470 + 8) | 4;
      FUN_800434a8(iVar13);
      *(undefined2 *)(iVar13 + 0x60) = 0;
      FUN_80040204(0x34);
      FUN_80015b28();
      return;
    }
    bVar2 = param_1[2];
    if (bVar2 == 1) {
      if ((DAT_8009c72c & 0x80e0) == 0) {
        return;
      }
      FUN_80015ba0();
      param_1[3] = 1;
      param_1[2] = 2;
      FUN_80040204(0x34);
      iVar13 = DAT_800eb470;
      FUN_800434a8(DAT_800eb470);
      *(undefined2 *)(iVar13 + 0x60) = 0;
      return;
    }
    if (bVar2 < 2) {
      if (bVar2 != 0) {
        return;
      }
      if (*(short *)(DAT_800eb470 + 0x60) < 0x800) {
        bVar2 = *(char *)(DAT_800eb470 + 0x21) - 4;
        *(byte *)(DAT_800eb470 + 0x21) = bVar2;
        if (bVar2 < 0xd7) {
          *(undefined1 *)(iVar13 + 0x21) = 0xd7;
        }
        sVar3 = *(short *)(iVar13 + 0x60) + 0xcc;
        *(short *)(iVar13 + 0x60) = sVar3;
        FUN_800434bc(iVar13,0xffffffea,0,(int)sVar3);
        if (0x7ff < *(short *)(iVar13 + 0x60)) {
          *(undefined1 *)(iVar13 + 0x21) = 0xd7;
          *(undefined2 *)(iVar13 + 0x30) = 0xffea;
          *(undefined2 *)(iVar13 + 0x32) = 0;
        }
      }
      sVar3 = *(short *)(param_1 + 0x10);
      *(short *)(param_1 + 0x10) = sVar3 + 0x2a;
      if ((short)(sVar3 + 0x2a) < 0x400) {
        return;
      }
      param_1[0x10] = 0;
      param_1[0x11] = 4;
      if ((DAT_800eb24e & 0x80) != 0) {
        return;
      }
      if (param_1[3] != 0) {
        return;
      }
      param_1[2] = 1;
      FUN_80040734(*(undefined4 *)(param_1 + 0x50));
      return;
    }
    if (bVar2 != 2) {
      return;
    }
    if ((*(ushort *)(DAT_800eb470 + 8) & 4) != 0) {
      sVar3 = *(short *)(DAT_800eb470 + 0x60) + 0xcc;
      *(char *)(DAT_800eb470 + 0x21) = *(char *)(DAT_800eb470 + 0x21) + '\x04';
      *(short *)(iVar13 + 0x60) = sVar3;
      FUN_800434bc(iVar13,2,0,(int)sVar3);
      if (0x7ff < *(short *)(iVar13 + 0x60)) {
        *(undefined1 *)(iVar13 + 0x21) = 0;
        *(undefined2 *)(iVar13 + 0x30) = 2;
        *(undefined2 *)(iVar13 + 0x32) = 0;
        *(ushort *)(iVar13 + 8) = *(ushort *)(iVar13 + 8) & 0xfffb;
      }
      if ((*(ushort *)(iVar13 + 8) & 4) != 0) {
        return;
      }
    }
    if ((DAT_800eb24e & 0x80) != 0) {
      return;
    }
    if (param_1[3] != 0) {
      return;
    }
    FUN_80048354();
    DAT_8009c8a0 = (code *)0x0;
    DAT_8009c424 = 0;
    FUN_80040734(*(undefined4 *)(param_1 + 0x50),2);
    goto LAB_8002b94c;
  case 5:
    if ((DAT_8009c72c & 0x20) == 0) {
      if ((((param_1[4] == 0) && ((DAT_8009c72c & 0x20c0) != 0)) &&
          (((int)(&DAT_801d4244)[*(ushort *)(param_1 + 6) - 1] >> 0x1a & 0x1fU) < 0x14)) &&
         (param_1[3] == 0)) {
        param_1[1] = 4;
      }
    }
    else {
      *(ushort *)(DAT_800eb470 + 8) = *(ushort *)(DAT_800eb470 + 8) | 4;
      param_1[1] = 6;
      param_1[4] = 0;
      FUN_80040690(*(undefined4 *)(param_1 + 0x50));
      FUN_80014ec0();
      FUN_80040204(0x31);
    }
    break;
  case 6:
    bVar2 = *(char *)(DAT_800eb470 + 0x21) + 8;
    *(byte *)(DAT_800eb470 + 0x21) = bVar2;
    if ((int)((uint)bVar2 << 0x18) < 0) {
      *(uint *)(DAT_800eb474 + 4) = *(uint *)(DAT_800eb474 + 4) | 0x80000000;
      *(uint *)(iVar13 + 4) = *(uint *)(iVar13 + 4) & 0xf7ffffff;
      FUN_800434a8(iVar13);
      iVar9 = 0;
      *(undefined2 *)(iVar13 + 0x60) = 0;
      pbVar11 = param_1;
      do {
        iVar9 = iVar9 + 1;
        *(ushort *)(*(int *)(pbVar11 + 0x24) + 8) = *(ushort *)(*(int *)(pbVar11 + 0x24) + 8) | 0x40
        ;
        pbVar11 = pbVar11 + 4;
      } while (iVar9 < 9);
      *(ushort *)(DAT_800f09a4 + 8) = *(ushort *)(DAT_800f09a4 + 8) | 0x40;
      DAT_8009c8a4 = &LAB_8002a05c;
      FUN_80015b28();
      param_1[3] = 2;
      param_1[1] = 7;
      FUN_80040204(0x33);
    }
    break;
  case 7:
    if (DAT_800eb470 == 0) {
      if (param_1[3] == 0) {
        FUN_80040690(*(undefined4 *)(param_1 + 0x4c));
        param_1[0x4c] = 0;
        param_1[0x4d] = 0;
        param_1[0x4e] = 0;
        param_1[0x4f] = 0;
        FUN_800360d8(&DAT_800f0850);
        param_1[1] = 8;
      }
    }
    else {
      FUN_8002ad44(DAT_800eb470,1);
      sVar3 = *(short *)(iVar13 + 0x60) + 0x66;
      *(char *)(iVar13 + 0x22) = *(char *)(iVar13 + 0x22) + '\f';
      *(char *)(iVar13 + 0x21) = *(char *)(iVar13 + 0x21) + '\x06';
      *(short *)(iVar13 + 0x60) = sVar3;
      FUN_800434bc(iVar13,((int)*(short *)(param_1 + 8) - (int)*(short *)(iVar13 + 0x48)) -
                          (int)DAT_8009c4c0,
                   ((int)*(short *)(param_1 + 10) - (int)*(short *)(iVar13 + 0x4a)) -
                   (int)DAT_8009c4c2,(int)sVar3);
      sVar3 = *(short *)(iVar13 + 0x44) + -0xcc;
      *(short *)(iVar13 + 0x44) = sVar3;
      *(short *)(iVar13 + 0x46) = sVar3;
      if (0x7ff < *(short *)(iVar13 + 0x60)) {
        FUN_800296c0(0);
        param_1[(uint)*(ushort *)(param_1 + 6) * 4 + 0x56] =
             param_1[(uint)*(ushort *)(param_1 + 6) * 4 + 0x56] | 0x80;
      }
    }
    break;
  case 8:
    *param_1 = 1;
  }
  return;
}

