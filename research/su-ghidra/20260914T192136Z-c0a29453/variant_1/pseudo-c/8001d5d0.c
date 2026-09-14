/* Analysis pseudo-C, not buildable source. */

void FUN_8001d5d0(void)

{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  uint uVar9;
  ushort *puVar10;
  undefined4 uVar11;
  uint uVar12;
  int *piVar13;
  undefined2 uVar14;
  int iVar15;
  
  iVar6 = (uint)DAT_8009c504 * 0x70;
  iVar15 = iVar6 + -0x7ff14c38;
  if ((DAT_8009c564 & 0x8000) == 0) {
    DAT_8009c564 = DAT_8009c564 | 0x8000;
    if ((DAT_800eb28c == 0) || (DAT_800eb2ac == 0)) {
      DAT_8009c584 = DAT_8009c504;
      if ((&DAT_800eb28c)[(uint)DAT_8009c504 * 0x10] == 0) {
        DAT_8009c584 = DAT_8009c504 ^ 1;
      }
      (&DAT_800eb278)[(uint)DAT_8009c584 * 0x20] = 2;
      DAT_8009c564 = 0xc;
      return;
    }
    DAT_8009c528 = 0;
    DAT_8009c4ec = '\0';
    DAT_8009c5b0 = iVar15;
    (&DAT_800eb3da)[iVar6] = 4;
    *(undefined2 *)(&DAT_800eb3d4 + iVar6) = 0xbe;
    (&DAT_800eb3e0)[iVar6] = 1;
    (&DAT_800eb3db)[iVar6] = 0;
    (&DAT_800eb3d9)[iVar6] = 0;
    DAT_8009c57e = 3;
    DAT_8009c585 = 1;
  }
  uVar5 = DAT_8009c564;
  switch(DAT_8009c585 & 0xf) {
  case 1:
    if (DAT_8009c57e == 0) {
      DAT_8009c585 = 3;
    }
    break;
  case 2:
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      FUN_800282a8();
      FUN_80070c04(&DAT_801a9800);
      DAT_8009c52e = 0;
      return;
    }
    uVar5 = DAT_8009c52e & 0xf;
    if (uVar5 == 1) {
      if ((DAT_8009c52e & 0x8000) == 0) {
        iVar7 = DAT_800ec219 - 1;
        DAT_8009c52e = DAT_8009c52e | 0x8000;
        DAT_8009c590 = 0xff;
        DAT_8009c510 = 2;
        DAT_8009c50f = (char)iVar7 + (char)(iVar7 / 5) * -5;
        if (5 < DAT_800ec219) {
          DAT_8009c510 = 3;
        }
      }
      iVar15 = FUN_8001d514(iVar15);
      if (iVar15 != 0) {
        return;
      }
      if ((DAT_800ec21a != 0) || (DAT_800ec21b != '\0')) {
        if (DAT_800ec21b == '\0') {
          DAT_8009c52e = 3;
          return;
        }
        if (5 < DAT_800ec219) {
          DAT_8009c52e = 3;
          return;
        }
        DAT_8009c52e = 2;
        return;
      }
      uVar9 = (uint)(byte)(&DAT_800919e0)
                          [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                           (uint)DAT_8009c504 * 0x14];
      if (((&DAT_801a7aee)[uVar9 * 0xe] & 0x8000) != 0) {
        uVar11 = (&DAT_801a7ad8)[uVar9 * 7];
        (&DAT_801a7aee)[uVar9 * 0xe] = (&DAT_801a7aee)[uVar9 * 0xe] | 0x4000;
        FUN_80017dcc(uVar11);
      }
    }
    else {
      if (uVar5 < 2) {
        if ((DAT_8009c52e & 0xf) != 0) {
          return;
        }
        iVar6 = FUN_80070c7c();
        if (iVar6 == 0) {
          return;
        }
        if (iVar6 != 3) {
          DAT_8009c52e = 1;
          return;
        }
        goto switchD_8001d6ec_caseD_b;
      }
      if (uVar5 != 2) {
        if (uVar5 != 3) {
          return;
        }
        if ((DAT_8009c52e & 0x8000) == 0) {
          uVar5 = DAT_8009c52e | 0x8000;
          piVar13 = &DAT_801a7ad8 +
                    (uint)(byte)(&DAT_800919e0)
                                [(char)(&DAT_800eb3d8)[iVar6] * 5 +
                                 (int)(char)(&DAT_800eb3d7)[iVar6] + (uint)DAT_8009c504 * 0x14] * 7;
          DAT_8009c52e = DAT_8009c52e | 0xc000;
          if (((&DAT_801a7aee)
               [(uint)(byte)(&DAT_800919e0)
                            [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                             (uint)DAT_8009c504 * 0x14] * 0xe] & 0x800) == 0) {
            DAT_8009c52e = uVar5;
            return;
          }
LAB_8001da48:
          iVar6 = *piVar13;
          *(code **)(iVar6 + 0x24) = FUN_8001d1a0;
          *(undefined1 *)(iVar6 + 0x6c) = 0xf;
          return;
        }
        if (((DAT_8009c52e & 0x4000) != 0) && (iVar15 = FUN_80042e70(0xf), iVar15 != 0)) {
          return;
        }
        DAT_8009c4ec = '\x01';
        goto LAB_8001dd60;
      }
      uVar9 = (uint)(byte)(&DAT_800919e0)
                          [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                           (uint)DAT_8009c504 * 0x14];
      piVar13 = &DAT_801a7ad8 + uVar9 * 7;
      uVar5 = DAT_8009c52e | 0x8000;
      if ((DAT_8009c52e & 0x8000) != 0) {
        iVar6 = FUN_80042e70(0xf);
        if (iVar6 != 0) {
          return;
        }
        iVar6 = *piVar13;
        (&DAT_801a7aee)[uVar9 * 0xe] = (&DAT_801a7aee)[uVar9 * 0xe] | 0x4000;
        FUN_80017dcc(iVar6);
        DAT_8009c585 = 2;
        return;
      }
      uVar3 = (&DAT_801a7aee)[uVar9 * 0xe];
      DAT_8009c52e = uVar5;
      if ((uVar3 & 0x8000) != 0) {
        if ((uVar3 & 0x800) == 0) goto LAB_8001da48;
        iVar6 = *piVar13;
        (&DAT_801a7aee)[uVar9 * 0xe] = uVar3 | 0x4000;
        FUN_80017dcc(iVar6);
      }
    }
LAB_8001dac8:
    DAT_8009c585 = 2;
    uVar5 = DAT_8009c564;
    break;
  case 3:
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c4ec = '\0';
      if (-1 < (char)(&DAT_8009c6f2)[DAT_8009c504]) goto LAB_8001dac8;
      DAT_8009c585 = DAT_8009c585 | 0xc0;
      (&DAT_800eb3e1)[iVar6] = 0;
    }
    iVar7 = FUN_80042e70(0xf);
    if (iVar7 != 0) {
      return;
    }
    iVar15 = FUN_8002411c(iVar15);
    if (iVar15 == 0) {
      bVar4 = DAT_8009c585 & 0xbf;
      if ((DAT_8009c585 & 0x40) != 0) {
        DAT_8009c585 = bVar4;
        if (((&DAT_800eb3d8)[iVar6] == '\x02') &&
           (iVar15 = FUN_80016f28(&DAT_801a7ad8 +
                                  (uint)(byte)(&DAT_800919ea)
                                              [(int)(char)(&DAT_800eb3d7)[iVar6] +
                                               (uint)DAT_8009c504 * 0x14] * 7), iVar15 != 0)) {
          DAT_8009c528 = FUN_8001d478(*(undefined4 *)(&DAT_800eb3cc + iVar6));
        }
        else {
          FUN_80040690(DAT_8009c528);
          DAT_8009c528 = 0;
        }
      }
      if (((char)(&DAT_8009c6f2)[DAT_8009c504] < '\0') && ((DAT_8009c72c & 0x800) != 0)) {
        DAT_8009c585 = 0xb;
        return;
      }
      iVar15 = FUN_8001bcbc();
      if (iVar15 != 0) {
        return;
      }
      if ((DAT_8009c72c & 0xc) != 0) {
        bVar4 = (&DAT_800919e0)
                [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                 (uint)DAT_8009c504 * 0x14];
        if ((char)(&DAT_800eb3d8)[iVar6] != 2) {
          return;
        }
        iVar6 = FUN_80016f28(&DAT_801a7ad8 + (uint)bVar4 * 7);
        if (iVar6 == 0) {
          return;
        }
        iVar6 = (&DAT_801a7ad8)[(uint)bVar4 * 7];
        *(code **)(iVar6 + 0x24) = FUN_8001d1a0;
        *(undefined1 *)(iVar6 + 0x6c) = 0xf;
        FUN_80040204(0xb);
        return;
      }
      iVar7 = FUN_80016f50(&DAT_801a7ad8 +
                           (uint)(byte)(&DAT_800919e0)
                                       [(char)(&DAT_800eb3d8)[iVar6] * 5 +
                                        (int)(char)(&DAT_800eb3d7)[iVar6] +
                                        (uint)DAT_8009c504 * 0x14] * 7);
      if (iVar7 != 0) {
LAB_8001e2cc:
        DAT_8009c5d8 = (short)iVar7;
        DAT_8009c5dc = 2;
        DAT_8009c5dd = 0x14;
        return;
      }
      if ((DAT_8009c72c & 0xc0) == 0) {
        return;
      }
      if ((((&DAT_800eb3d8)[iVar6] == '\x02') &&
          ((*(char *)(DAT_8009c500 + 0x19) != '\0' || ((DAT_8009c582 & 0x1000) != 0)))) ||
         ((char)(&DAT_800eb3d8)[iVar6] < '\x02')) goto LAB_8001e414;
LAB_8001dd60:
      bVar4 = (&DAT_800919e0)
              [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
               (uint)DAT_8009c504 * 0x14];
      if ((*(uint *)(&DAT_801a7aec + (uint)bVar4 * 0xe) & 0xc8000000) == 0x80000000) {
        FUN_80040204(7);
        FUN_80040690(DAT_8009c528);
        DAT_8009c528 = 0;
        if ((char)(&DAT_800eb3d8)[iVar6] < '\x02') {
          DAT_8009c528 = 0;
          return;
        }
        iVar15 = (uint)DAT_8009c504 * 0x70;
        if ('\x02' < (char)(&DAT_800eb3d8)[iVar6]) {
          if (((int)(&DAT_801d4244)[*(short *)(&DAT_801a7ae4 + (uint)bVar4 * 0x1c) + -1] >> 0x1a &
              0x1fU) != 0x17) {
            DAT_8009c528 = 0;
            DAT_8009c585 = 7;
            return;
          }
          (&DAT_800eb3f5)[iVar15] = 2;
          (&DAT_800eb3f4)[iVar15] = 2;
          (&DAT_800eb3f6)[iVar15] = 3;
          DAT_8009c585 = 4;
          return;
        }
        DAT_8009c585 = 4;
        (&DAT_800eb3f5)[iVar15] = 1;
        (&DAT_800eb3f6)[iVar15] = 2;
        (&DAT_800eb3f4)[iVar15] = 1;
        return;
      }
      goto LAB_8001e414;
    }
    goto LAB_8001e260;
  case 4:
    iVar6 = (uint)DAT_8009c504 * 0x70;
    iVar15 = iVar6 + -0x7ff14c1c;
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      DAT_8009c5b0 = iVar15;
      (&DAT_800eb3fc)[iVar6] = 0;
      *(undefined2 *)(iVar6 + -0x7ff14c10) = 0x84;
      FUN_800235a0(iVar15);
      FUN_80022e50(0x10,0x14e,0x3fe,*(undefined2 *)(&DAT_8009c2b0 + (uint)DAT_8009c504 * 2),
                   (int)*(short *)(&DAT_800919b4 +
                                  (char)(&DAT_800eb3f4)[iVar6] * 2 +
                                  (uint)(byte)(&DAT_800eb3fc)[iVar6] * 8 + (uint)DAT_8009c504 * 0x10
                                  ));
      iVar7 = *(int *)(&DAT_800eb3e8 + iVar6);
      iVar15 = *(int *)(&DAT_800eb3cc + (uint)DAT_8009c504 * 0x70);
      FUN_80042d08(iVar7);
      *(undefined2 *)(iVar7 + 0x60) = 0x10;
      *(undefined1 *)(iVar7 + 0x6c) = 0;
      *(undefined4 *)(iVar7 + 0x2c) = *(undefined4 *)(iVar7 + 0x28);
      iVar6 = ((int)*(short *)(iVar7 + 0x28) - (int)*(short *)(iVar15 + 0x28)) * 0x100;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xf;
      }
      *(short *)(iVar7 + 0x36) = (short)(iVar6 >> 4);
      iVar6 = ((int)*(short *)(iVar7 + 0x2a) - (int)*(short *)(iVar15 + 0x2a)) * 0x100;
      if (iVar6 < 0) {
        iVar6 = iVar6 + 0xf;
      }
      *(short *)(iVar7 + 0x3a) = (short)(iVar6 >> 4);
      DAT_8009c57e = 0x52;
      *(undefined4 *)(iVar7 + 0x28) = *(undefined4 *)(iVar15 + 0x28);
      uVar5 = DAT_8009c564;
    }
    else if (DAT_8009c57e == 0) {
      FUN_80023548(iVar15);
      DAT_8009c585 = 6;
      uVar5 = DAT_8009c564;
      if (DAT_8009c4ec != '\0') {
        DAT_8009c585 = 5;
      }
    }
    break;
  case 5:
    iVar15 = (uint)DAT_8009c504 * 0x70 + -0x7ff14c1c;
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      DAT_8009c568 = 0;
      if (DAT_800ec21a < 0x38) {
        if (DAT_800ec21a < 6) {
          DAT_8009c50f = DAT_800ec21a - 1;
          DAT_8009c510 = 2;
        }
        else {
          DAT_8009c50f = DAT_800ec21a - 6;
          DAT_8009c510 = 3;
        }
      }
      else {
        DAT_8009c50f = '<' - DAT_800ec21a;
        DAT_8009c510 = 1;
      }
    }
    iVar6 = FUN_8001d514(iVar15);
    if (iVar6 != 0) {
      return;
    }
LAB_8001e330:
    bVar1 = false;
    iVar6 = (int)*(char *)(iVar15 + 0x10);
    iVar7 = 5;
    if (iVar6 == 1) {
      bVar1 = true;
      iVar6 = 0;
      do {
        iVar6 = iVar6 + 1;
        if (((&DAT_801a7aee)[(uint)(byte)(&DAT_800919e0)[iVar7 + (uint)DAT_8009c504 * 0x14] * 0xe] &
            0x8000) != 0) {
          bVar1 = false;
          break;
        }
        iVar7 = iVar7 + 1;
      } while (iVar6 < 5);
      iVar6 = (int)*(char *)(iVar15 + 0x10);
    }
    if ((!bVar1) &&
       (((&DAT_801a7aee)
         [(uint)(byte)(&DAT_800919e0)
                      [iVar6 * 5 + (int)*(char *)(iVar15 + 0xf) + (uint)DAT_8009c504 * 0x14] * 0xe]
        & 0x8000) == 0)) {
LAB_8001e414:
      FUN_80040204(9);
      return;
    }
    FUN_80040204(7);
    iVar6 = 6;
    puVar8 = &DAT_800eb388;
    do {
      *puVar8 = 0;
      iVar6 = iVar6 + -1;
      puVar8 = puVar8 + -1;
    } while (-1 < iVar6);
    iVar6 = (uint)DAT_8009c504 * 0x70;
    uVar9 = (uint)(byte)(&DAT_800919e0)
                        [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                         (uint)DAT_8009c504 * 0x14];
    iVar6 = uVar9 * 0x1c;
    DAT_8009c594 = (&DAT_801a7aee)[uVar9 * 0xe];
    DAT_8009c554 = *(undefined2 *)(&DAT_801a7aea + iVar6);
    iVar7 = FUN_80017e94(&DAT_801a7ad8 + uVar9 * 7,(int)*(short *)(&DAT_801a7ae0 + iVar6),
                         (int)*(short *)(&DAT_801a7ae2 + iVar6));
    FUN_80042c1c(iVar7,0xfffffff6);
    sVar2 = *(short *)(&DAT_801a7ae4 + iVar6);
    DAT_800eb370 = iVar7;
    FUN_800249d0();
    uVar9 = (uint)(byte)(&DAT_800919e0)
                        [*(char *)(iVar15 + 0x10) * 5 + (int)*(char *)(iVar15 + 0xf) +
                         (uint)DAT_8009c504 * 0x14];
    iVar6 = uVar9 * 0x1c;
    if (bVar1) {
      uVar5 = 9;
    }
    else {
      DAT_8009c596 = (&DAT_801a7aee)[uVar9 * 0xe];
      DAT_8009c556 = *(undefined2 *)(&DAT_801a7aea + iVar6);
      DAT_800eb374 = FUN_80017e94(&DAT_801a7ad8 + uVar9 * 7,(int)*(short *)(&DAT_801a7ae0 + iVar6),
                                  (int)*(short *)(&DAT_801a7ae2 + iVar6));
      DAT_8009c59c = *(undefined1 *)(DAT_800eb374 + 0x6a);
      FUN_800249d0(&DAT_801a7ad8 + uVar9 * 7);
      uVar5 = 9;
      if (((int)(&DAT_801d4244)[sVar2 + -1] >> 0x1a & 0x1fU) == 0x17) {
        DAT_8009c585 = 8;
        return;
      }
    }
    break;
  case 6:
    iVar6 = (uint)DAT_8009c504 * 0x70;
    iVar15 = iVar6 + -0x7ff14c1c;
    if ((DAT_8009c585 & 0x80) != 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      DAT_8009c5b0 = iVar15;
    }
    if ((DAT_8009c585 & 0x40) != 0) {
      if (DAT_8009c57e != 0) {
        return;
      }
      FUN_80040690(*(undefined4 *)(&DAT_800eb3e8 + iVar6));
      bVar4 = DAT_8009c504;
      *(undefined4 *)(&DAT_800eb3e8 + iVar6) = 0;
      DAT_8009c585 = 3;
LAB_8001eaec:
      DAT_8009c5b0 = (uint)bVar4 * 0x70 + -0x7ff14c38;
      return;
    }
    iVar7 = FUN_8002411c(iVar15);
    if (iVar7 != 0) {
      return;
    }
    if ((DAT_8009c72c & 0x20) == 0) {
      iVar7 = FUN_80016f50(&DAT_801a7ad8 +
                           (uint)(byte)(&DAT_800919e0)
                                       [(char)(&DAT_800eb3f4)[iVar6] * 5 +
                                        (int)(char)(&DAT_800eb3f3)[iVar6] +
                                        (uint)DAT_8009c504 * 0x14] * 7);
      if (iVar7 != 0) goto LAB_8001e2cc;
      if ((DAT_8009c72c & 0xc0) == 0) {
        return;
      }
      DAT_8009c568 = (DAT_8009c72c & 0x80) != 0;
      goto LAB_8001e330;
    }
    uVar9 = (uint)DAT_8009c504;
    FUN_80022e50(0x10,0x14e,0x3fe,*(undefined2 *)(&DAT_8009c2b0 + uVar9 * 2),
                 (int)*(short *)(&DAT_800919b4 +
                                (char)(&DAT_800eb3d8)[uVar9 * 0x70] * 2 +
                                (uint)(byte)(&DAT_800eb3e0)[uVar9 * 0x70] * 8 + uVar9 * 0x10));
    iVar7 = *(int *)(&DAT_800eb3e8 + iVar6);
    iVar15 = *(int *)(&DAT_800eb3cc + (uint)DAT_8009c504 * 0x70);
    FUN_80042d08(iVar7);
    *(undefined2 *)(iVar7 + 0x60) = 0x10;
    *(undefined1 *)(iVar7 + 0x6c) = 0;
    iVar6 = ((int)*(short *)(iVar15 + 0x28) - (int)*(short *)(iVar7 + 0x28)) * 0x100;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xf;
    }
    *(short *)(iVar7 + 0x36) = (short)(iVar6 >> 4);
    iVar6 = ((int)*(short *)(iVar15 + 0x2a) - (int)*(short *)(iVar7 + 0x2a)) * 0x100;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xf;
    }
    *(short *)(iVar7 + 0x3a) = (short)(iVar6 >> 4);
    *(undefined4 *)(iVar7 + 0x2c) = *(undefined4 *)(iVar15 + 0x28);
    DAT_8009c57e = 0x58;
LAB_8001e260:
    DAT_8009c585 = DAT_8009c585 | 0x40;
    uVar5 = DAT_8009c564;
    break;
  case 7:
    if ((DAT_8009c585 & 0x80) == 0) {
      uVar9 = (uint)(byte)(&DAT_800919e0)
                          [(char)(&DAT_800eb3d8)[iVar6] * 5 + (int)(char)(&DAT_800eb3d7)[iVar6] +
                           (uint)DAT_8009c504 * 0x14];
      piVar13 = &DAT_801a7ad8;
      DAT_8009c585 = DAT_8009c585 | 0x80;
      DAT_8009c5b8 = FUN_80017e94(&DAT_801a7ad8 + uVar9 * 7,
                                  (int)*(short *)(&DAT_801a7ae0 + uVar9 * 0x1c),
                                  (int)*(short *)(&DAT_801a7ae2 + uVar9 * 0x1c));
      uVar5 = (&DAT_801a7aee)[uVar9 * 0xe];
      (&DAT_801a7aee)[uVar9 * 0xe] = uVar5 & 0x7fff;
      if ((uVar5 & 0x1000) != 0) {
        *(undefined1 *)(DAT_8009c5b8 + 0x21) = 0x80;
        *(ushort *)(DAT_8009c5b8 + 8) = *(ushort *)(DAT_8009c5b8 + 8) | 4;
      }
      *(undefined2 *)(DAT_8009c5b8 + 0x60) = 0xc;
      *(code **)(DAT_8009c5b8 + 0x24) = FUN_8001d324;
      *(undefined2 *)(DAT_8009c5b8 + 0x28) = 0x86;
      *(undefined2 *)(DAT_8009c5b8 + 0x2a) = 0x5a;
      *(undefined2 *)(DAT_8009c5b8 + 0x2c) = 0;
      *(undefined1 *)(DAT_8009c5b8 + 0x6c) = 1;
      bVar1 = DAT_8009c4ec == '\0';
      *(ushort *)(*(int *)(&DAT_800eb3cc + iVar6) + 8) =
           *(ushort *)(*(int *)(&DAT_800eb3cc + iVar6) + 8) & 0xffbf;
      uVar5 = DAT_8009c564;
      if (bVar1) {
        DAT_8009c4f0 = 0x202020;
        iVar6 = 0;
        puVar10 = &DAT_801a7aee;
        do {
          if ((*puVar10 & 0x8000) != 0) {
            iVar15 = *piVar13;
            *(undefined1 *)(iVar15 + 0x6c) = 1;
            *(undefined2 *)(iVar15 + 0x60) = 8;
            *(undefined1 **)(iVar15 + 0x24) = &LAB_8001d2a4;
            uVar14 = 0x20;
            if ((*puVar10 & 0x4000) != 0) {
              uVar14 = 0x10;
            }
            *(undefined2 *)(iVar15 + 0x2c) = uVar14;
            *(undefined2 *)(iVar15 + 0x2a) = uVar14;
            *(undefined2 *)(iVar15 + 0x28) = uVar14;
          }
          puVar10 = puVar10 + 0xe;
          iVar6 = iVar6 + 1;
          piVar13 = piVar13 + 7;
        } while (iVar6 < 0x1e);
        DAT_8009c560 = 0;
        DAT_8009c585 = DAT_8009c585 | 0x20;
        uVar5 = DAT_8009c564;
      }
    }
    else {
      if (DAT_8009c4ec == '\0') {
        if ((DAT_8009c585 & 0x20) != 0) {
          uVar9 = DAT_8009c688 & 0xff;
          uVar12 = DAT_8009c4f0 & 0xff;
          if (uVar9 < uVar12) {
            uVar9 = uVar9 + 8;
            bVar1 = uVar12 < uVar9;
          }
          else {
            uVar9 = uVar9 - 8;
            bVar1 = (int)uVar9 < (int)uVar12;
          }
          if (bVar1) {
            uVar9 = uVar12;
          }
          DAT_8009c688 = uVar9 << 0x10 | uVar9 << 8 | uVar9;
          if (DAT_8009c688 != DAT_8009c4f0) {
            return;
          }
          iVar6 = FUN_80042e70(1);
          if (iVar6 != 0) {
            return;
          }
          DAT_8009c585 = DAT_8009c585 & 0xdf;
          return;
        }
        if ((DAT_8009c585 & 0x40) == 0) {
          iVar6 = FUN_800208e8();
          if (iVar6 == 0) {
            return;
          }
          if (iVar6 == 1) {
            FUN_80040204(7);
          }
          else {
            DAT_8009c585 = DAT_8009c585 | 0x10;
            FUN_80040204(8);
            iVar6 = DAT_8009c5b8;
            *(undefined2 *)(DAT_8009c5b8 + 0x60) = 0xc;
            *(code **)(iVar6 + 0x24) = FUN_8001d324;
            *(undefined2 *)(iVar6 + 0x28) =
                 *(undefined2 *)(&DAT_801a7ae0 + (uint)*(byte *)(iVar6 + 0x6a) * 0x1c);
            uVar14 = *(undefined2 *)(&DAT_801a7ae2 + (uint)*(byte *)(iVar6 + 0x6a) * 0x1c);
            *(undefined2 *)(iVar6 + 0x2c) = 0;
            *(undefined2 *)(iVar6 + 0x2a) = uVar14;
            if (((&DAT_801a7aee)[(uint)*(byte *)(iVar6 + 0x6a) * 0xe] & 0x1000) != 0) {
              *(undefined2 *)(iVar6 + 0x2c) = 0x80;
            }
            *(undefined1 *)(iVar6 + 0x6c) = 1;
          }
          piVar13 = &DAT_801a7ad8;
          iVar6 = 0;
          puVar10 = &DAT_801a7aee;
          DAT_8009c4f0 = 0x808080;
          DAT_8009c585 = DAT_8009c585 | 0x60;
          do {
            if ((*puVar10 & 0x8000) != 0) {
              iVar15 = *piVar13;
              *(undefined1 *)(iVar15 + 0x6c) = 1;
              *(undefined2 *)(iVar15 + 0x60) = 8;
              *(undefined1 **)(iVar15 + 0x24) = &LAB_8001d2a4;
              uVar14 = 0x80;
              if ((*puVar10 & 0x4000) != 0) {
                uVar14 = 0x40;
              }
              *(undefined2 *)(iVar15 + 0x2c) = uVar14;
              *(undefined2 *)(iVar15 + 0x2a) = uVar14;
              *(undefined2 *)(iVar15 + 0x28) = uVar14;
            }
            puVar10 = puVar10 + 0xe;
            iVar6 = iVar6 + 1;
            piVar13 = piVar13 + 7;
          } while (iVar6 < 0x1e);
          return;
        }
        if ((DAT_8009c585 & 0x10) != 0) {
          (&DAT_801a7aee)[(uint)*(byte *)(DAT_8009c5b8 + 0x6a) * 0xe] =
               (&DAT_801a7aee)[(uint)*(byte *)(DAT_8009c5b8 + 0x6a) * 0xe] | 0x8000;
          FUN_80040690();
          DAT_8009c585 = 3;
          *(ushort *)(*(int *)(&DAT_800eb3cc + iVar6) + 8) =
               *(ushort *)(*(int *)(&DAT_800eb3cc + iVar6) + 8) | 0x40;
          return;
        }
      }
      else {
        iVar6 = FUN_80042e70(1);
        if (iVar6 != 0) {
          return;
        }
      }
      FUN_80024a10(&DAT_801a7ad8 + (uint)*(byte *)(DAT_8009c5b8 + 0x6a) * 7);
      DAT_8009c585 = 9;
      DAT_800eb370 = DAT_8009c5b8;
      uVar5 = DAT_8009c564;
    }
    break;
  case 8:
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c5b0 = (uint)DAT_8009c504 * 0x70 + -0x7ff14c1c;
      DAT_8009c585 = DAT_8009c585 | 0x80;
      FUN_80040690(*(undefined4 *)(&DAT_800eb3e8 + (uint)DAT_8009c504 * 0x70));
      DAT_8009c57e = 8;
      *(undefined4 *)(DAT_8009c5b0 + 4) = 0;
    }
    if (DAT_8009c57e != 0) {
      return;
    }
    uVar5 = 7;
    if ((DAT_8009c585 & 0x40) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x40;
      DAT_8009c57e = 0xc;
      bVar4 = DAT_8009c504;
      goto LAB_8001eaec;
    }
    break;
  case 9:
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c57e = 0xc;
      DAT_8009c585 = DAT_8009c585 | 0x80;
    }
    uVar5 = 6;
    goto joined_r0x8001eb98;
  case 10:
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c57e = 0xc;
      DAT_8009c585 = DAT_8009c585 | 0x80;
    }
    uVar5 = 10;
joined_r0x8001eb98:
    if (DAT_8009c57e != 0) {
      return;
    }
    break;
  case 0xb:
switchD_8001d6ec_caseD_b:
    DAT_8009c582 = DAT_8009c582 & 0xefff;
    FUN_80040690(DAT_8009c528);
    DAT_8009c528 = 0;
    DAT_8009c585 = 10;
    FUN_80040204(0x30);
    uVar5 = DAT_8009c564;
  }
  DAT_8009c564 = uVar5;
  return;
}

