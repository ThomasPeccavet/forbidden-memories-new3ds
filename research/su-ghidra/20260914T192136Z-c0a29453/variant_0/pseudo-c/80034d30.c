/* Analysis pseudo-C, not buildable source. */

/* WARNING: Heritage AFTER dead removal. Example location: r0x1f8003a0 : 0x8003556c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

int FUN_80034d30(int *param_1,undefined4 param_2,uint param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 in_zero;
  undefined4 in_at;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  short *psVar12;
  short *psVar13;
  short *psVar14;
  short *psVar15;
  ushort *puVar16;
  undefined2 *puVar17;
  uint *puVar18;
  uint *puVar19;
  int iVar20;
  uint uVar21;
  undefined2 *puVar22;
  uint uVar23;
  uint uVar24;
  int iVar25;
  
  if ((DAT_8009c68c & 8) == 0) {
    iVar3 = *param_1;
    puVar18 = (uint *)param_1[4];
    uVar21 = (uint)*(ushort *)(iVar3 + 2);
    iVar20 = param_1[6];
    iVar25 = param_1[7];
    puVar22 = (undefined2 *)(param_1[5] + (*(uint *)(iVar3 + 4) & 0xffffff) * 4);
    if ((DAT_8009c68c & 4) == 0) {
      if ((DAT_8009c68c & 3) == 0) {
        iVar11 = uVar21 - 1;
        _DAT_1f8003c0 = DAT_8009c688;
        if (iVar11 != -1) {
          puVar17 = puVar22 + 1;
          do {
            puVar4 = (undefined4 *)(iVar20 + (uint)(ushort)puVar17[6] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            copFunction(2,0x180001);
            _DAT_1f800388 = getCopReg(2,0xe);
            _DAT_1f8003e0 = getCopControlWord(2,0xf800);
            puVar4 = (undefined4 *)(iVar25 + (uint)(ushort)puVar17[4] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            setCopReg(2,param_3,_DAT_1f8003c0);
            copFunction(2,0xe80413);
            _DAT_1f800384 = getCopReg(2,0x16);
            _DAT_1f8003f0 = getCopReg(2,0x9800);
            _DAT_1f8003f0 = _DAT_1f8003f0 >> 2;
            puVar4 = (undefined4 *)(iVar20 + (uint)(ushort)puVar17[8] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            copFunction(2,0x180001);
            _DAT_1f800394 = getCopReg(2,0xe);
            _DAT_1f8003e4 = getCopControlWord(2,0xf800);
            puVar4 = (undefined4 *)(iVar25 + (uint)(ushort)puVar17[7] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            setCopReg(2,param_3,_DAT_1f8003c0);
            copFunction(2,0xe80413);
            _DAT_1f800390 = getCopReg(2,0x16);
            _DAT_1f8003f4 = getCopReg(2,0x9800);
            _DAT_1f8003f4 = _DAT_1f8003f4 >> 2;
            puVar4 = (undefined4 *)(iVar20 + (uint)(ushort)puVar17[10] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            copFunction(2,0x180001);
            _DAT_1f8003a0 = getCopReg(2,0xe);
            _DAT_1f8003e8 = getCopControlWord(2,0xf800);
            puVar4 = (undefined4 *)(iVar25 + (uint)(ushort)puVar17[9] * 8);
            setCopReg(2,in_zero,*puVar4);
            setCopReg(2,in_at,puVar4[1]);
            setCopReg(2,param_3,_DAT_1f8003c0);
            copFunction(2,0xe80413);
            _DAT_1f80039c = getCopReg(2,0x16);
            _DAT_1f8003f8 = getCopReg(2,0x9800);
            _DAT_1f8003f8 = _DAT_1f8003f8 >> 2;
            setCopReg(2,0x6000,_DAT_1f800388);
            setCopReg(2,0x7000,_DAT_1f8003a0);
            setCopReg(2,0x6800,_DAT_1f800394);
            copFunction(2,0x1400006);
            iVar5 = getCopReg(2,0x18);
            if ((0 < iVar5) && (-1 < (int)(_DAT_1f8003e0 | _DAT_1f8003e4 | _DAT_1f8003e8))) {
              puVar4 = (undefined4 *)(iVar20 + (uint)(ushort)puVar17[0xc] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f8003ac = getCopReg(2,0xe);
              _DAT_1f8003ec = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)(ushort)puVar17[0xb] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003c0);
              copFunction(2,0xe80413);
              _DAT_1f8003a8 = getCopReg(2,0x16);
              _DAT_1f8003fc = getCopReg(2,0x9800);
              _DAT_1f8003fc = _DAT_1f8003fc >> 2;
              DAT_1f800383 = 0xc;
              _DAT_1f800384 = CONCAT13(0x3c,_DAT_1f800384);
              param_3 = (uint)(ushort)puVar17[5];
              _DAT_1f800398 = *(undefined4 *)(puVar17 + 1);
              _DAT_1f8003a4 = CONCAT22(DAT_1f8003a4_2,puVar17[3]);
              _DAT_1f8003b0 = CONCAT22(DAT_1f8003b0_2,puVar17[5]);
              _DAT_1f80038c = CONCAT22(*puVar17,*puVar22);
              puVar10 = (uint *)&DAT_1f800380;
              puVar7 = puVar18;
              do {
                uVar21 = puVar10[1];
                uVar23 = puVar10[2];
                uVar24 = puVar10[3];
                *puVar7 = *puVar10;
                puVar7[1] = uVar21;
                puVar7[2] = uVar23;
                puVar7[3] = uVar24;
                puVar10 = puVar10 + 4;
                puVar7 = puVar7 + 4;
              } while (puVar10 != (uint *)&DAT_1f8003b0);
              *puVar7 = _DAT_1f8003b0;
              iVar5 = _DAT_1f8003f0 + _DAT_1f8003f4 + _DAT_1f8003f8 + _DAT_1f8003fc;
              if (iVar5 < 0) {
                iVar5 = iVar5 + 3;
              }
              iVar5 = (iVar5 >> 6) * 4;
              *puVar18 = *puVar18 & 0xff000000 |
                         *(uint *)(iVar5 + *(int *)(param_1[1] + 4)) & 0xffffff;
              uVar21 = (uint)puVar18 & 0xffffff;
              puVar10 = (uint *)(iVar5 + *(int *)(param_1[1] + 4));
              puVar18 = puVar18 + 0xd;
              *puVar10 = *puVar10 & 0xff000000 | uVar21;
            }
            puVar17 = puVar17 + 0xe;
            iVar11 = iVar11 + -1;
            puVar22 = puVar22 + 0xe;
          } while (iVar11 != -1);
        }
      }
      else {
        iVar11 = uVar21 - 1;
        _DAT_1f8003c0 = 0xffffff;
        _DAT_1f8003d0 = DAT_8009c688;
        if (iVar11 != -1) {
          puVar16 = puVar22 + 10;
          iVar5 = (int)puVar18 + 7;
          do {
            if (((DAT_8009c68c & 2) == 0) ||
               (psVar12 = (short *)(DAT_8009c690 + 6), DAT_8009c690 = DAT_8009c690 + 8,
               DAT_8009c694 <= (uint)(int)*psVar12)) {
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[-3] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f800388 = getCopReg(2,0xe);
              _DAT_1f8003e0 = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[-5] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003c0);
              copFunction(2,0xe80413);
              _DAT_1f800384 = getCopReg(2,0x16);
              _DAT_1f8003f0 = getCopReg(2,0x9800);
              _DAT_1f8003f0 = _DAT_1f8003f0 >> 2;
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[-1] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f800390 = getCopReg(2,0xe);
              getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[-2] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003c0);
              copFunction(2,0xe80413);
              _DAT_1f80038c = getCopReg(2,0x16);
              _DAT_1f8003f4 = getCopReg(2,0x9800);
              _DAT_1f8003f4 = _DAT_1f8003f4 >> 2;
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[3] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f800398 = getCopReg(2,0xe);
              _DAT_1f8003e8 = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[2] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003c0);
              copFunction(2,0xe80413);
              _DAT_1f800394 = getCopReg(2,0x16);
              _DAT_1f8003f8 = getCopReg(2,0x9800);
              _DAT_1f8003f8 = _DAT_1f8003f8 >> 2;
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[1] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f8003a0 = getCopReg(2,0xe);
              _DAT_1f8003ec = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)*puVar16 * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003c0);
              copFunction(2,0xe80413);
              _DAT_1f80039c = getCopReg(2,0x16);
              _DAT_1f8003fc = getCopReg(2,0x9800);
              _DAT_1f8003fc = _DAT_1f8003fc >> 2;
              if (-1 < (int)(_DAT_1f8003e0 | _DAT_1f8003e4 | _DAT_1f8003e8 | _DAT_1f8003ec)) {
                DAT_1f800383 = 9;
                _DAT_1f800384 = CONCAT13(0x5c,_DAT_1f800384);
                _DAT_1f8003a4 = 0x55555555;
                _DAT_1f800394 = _DAT_1f800394 & 0xffffff;
                _DAT_1f80039c = _DAT_1f80039c & 0xffffff;
                puVar10 = (uint *)&DAT_1f800380;
                puVar7 = puVar18;
                do {
                  puVar8 = puVar7;
                  puVar19 = puVar10;
                  uVar21 = puVar19[1];
                  uVar23 = puVar19[2];
                  uVar24 = puVar19[3];
                  *puVar8 = *puVar19;
                  puVar8[1] = uVar21;
                  puVar8[2] = uVar23;
                  puVar8[3] = uVar24;
                  puVar10 = puVar19 + 4;
                  puVar7 = puVar8 + 4;
                } while (puVar19 + 4 != (uint *)&DAT_1f8003a0);
                uVar21 = puVar19[5];
                puVar8[4] = _DAT_1f8003a0;
                puVar8[5] = uVar21;
                iVar6 = _DAT_1f8003f0 + _DAT_1f8003f4 + _DAT_1f8003f8 + _DAT_1f8003fc;
                if (iVar6 < 0) {
                  iVar6 = iVar6 + 3;
                }
                iVar9 = (iVar6 >> 6) * 4;
                *puVar18 = *puVar18 & 0xff000000 |
                           *(uint *)(iVar9 + *(int *)(param_1[1] + 4)) & 0xffffff;
                uVar2 = _DAT_1f800388;
                puVar10 = (uint *)(iVar9 + *(int *)(param_1[1] + 4));
                *puVar10 = *puVar10 & 0xff000000 | (uint)puVar18 & 0xffffff;
                *(undefined4 *)(iVar5 + 0x29) = uVar2;
                *(uint *)(iVar5 + 0x31) = _DAT_1f8003a0;
                puVar10 = puVar18 + 10;
                *(undefined4 *)(iVar5 + 0x25) = _DAT_1f800384;
                uVar21 = _DAT_1f80039c;
                *(undefined1 *)(iVar5 + 0x24) = 4;
                *(undefined1 *)(iVar5 + 0x28) = 0x50;
                *(uint *)(iVar5 + 0x2d) = uVar21;
                iVar6 = (iVar6 >> 6) * 4;
                *puVar10 = *puVar10 & 0xff000000 |
                           *(uint *)(iVar6 + *(int *)(param_1[1] + 4)) & 0xffffff;
                iVar5 = iVar5 + 0x3c;
                puVar7 = (uint *)(iVar6 + *(int *)(param_1[1] + 4));
                uVar21 = *puVar7;
                puVar19 = puVar18 + 0xf;
                goto LAB_8003568c;
              }
            }
            else {
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[-3] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f800388 = getCopReg(2,0xe);
              _DAT_1f8003e0 = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[-5] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003d0);
              copFunction(2,0xe80413);
              _DAT_1f800384 = getCopReg(2,0x16);
              _DAT_1f8003f0 = getCopReg(2,0x9800);
              _DAT_1f8003f0 = _DAT_1f8003f0 >> 2;
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[-1] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f800394 = getCopReg(2,0xe);
              _DAT_1f8003e4 = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[-2] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003d0);
              copFunction(2,0xe80413);
              _DAT_1f800390 = getCopReg(2,0x16);
              _DAT_1f8003f4 = getCopReg(2,0x9800);
              _DAT_1f8003f4 = _DAT_1f8003f4 >> 2;
              puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[1] * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              copFunction(2,0x180001);
              _DAT_1f8003a0 = getCopReg(2,0xe);
              _DAT_1f8003e8 = getCopControlWord(2,0xf800);
              puVar4 = (undefined4 *)(iVar25 + (uint)*puVar16 * 8);
              setCopReg(2,in_zero,*puVar4);
              setCopReg(2,in_at,puVar4[1]);
              setCopReg(2,param_3,_DAT_1f8003d0);
              copFunction(2,0xe80413);
              _DAT_1f80039c = getCopReg(2,0x16);
              _DAT_1f8003f8 = getCopReg(2,0x9800);
              _DAT_1f8003f8 = _DAT_1f8003f8 >> 2;
              setCopReg(2,0x6000,_DAT_1f800388);
              setCopReg(2,0x7000,_DAT_1f8003a0);
              setCopReg(2,0x6800,_DAT_1f800394);
              copFunction(2,0x1400006);
              iVar6 = getCopReg(2,0x18);
              if ((0 < iVar6) && (-1 < (int)(_DAT_1f8003e0 | _DAT_1f8003e4 | _DAT_1f8003e8))) {
                puVar4 = (undefined4 *)(iVar20 + (uint)puVar16[3] * 8);
                setCopReg(2,in_zero,*puVar4);
                setCopReg(2,in_at,puVar4[1]);
                copFunction(2,0x180001);
                _DAT_1f8003ac = getCopReg(2,0xe);
                _DAT_1f8003ec = getCopControlWord(2,0xf800);
                puVar4 = (undefined4 *)(iVar25 + (uint)puVar16[2] * 8);
                setCopReg(2,in_zero,*puVar4);
                setCopReg(2,in_at,puVar4[1]);
                setCopReg(2,param_3,_DAT_1f8003d0);
                copFunction(2,0xe80413);
                _DAT_1f8003a8 = getCopReg(2,0x16);
                _DAT_1f8003fc = getCopReg(2,0x9800);
                _DAT_1f8003fc = _DAT_1f8003fc >> 2;
                DAT_1f800383 = 0xc;
                _DAT_1f800384 = CONCAT13(0x3c,_DAT_1f800384);
                param_3 = (uint)puVar16[-4];
                _DAT_1f800398 = *(undefined4 *)(puVar16 + -8);
                _DAT_1f8003a4 = CONCAT22(DAT_1f8003a4_2,puVar16[-6]);
                _DAT_1f8003b0 = CONCAT22(DAT_1f8003b0_2,puVar16[-4]);
                _DAT_1f80038c = CONCAT22(puVar16[-9],*puVar22);
                puVar10 = (uint *)&DAT_1f800380;
                puVar7 = puVar18;
                do {
                  uVar21 = puVar10[1];
                  uVar23 = puVar10[2];
                  uVar24 = puVar10[3];
                  *puVar7 = *puVar10;
                  puVar7[1] = uVar21;
                  puVar7[2] = uVar23;
                  puVar7[3] = uVar24;
                  puVar10 = puVar10 + 4;
                  puVar7 = puVar7 + 4;
                } while (puVar10 != (uint *)&DAT_1f8003b0);
                *puVar7 = _DAT_1f8003b0;
                iVar6 = _DAT_1f8003f0 + _DAT_1f8003f4 + _DAT_1f8003f8 + _DAT_1f8003fc;
                if (iVar6 < 0) {
                  iVar6 = iVar6 + 3;
                }
                iVar6 = (iVar6 >> 6) * 4;
                *puVar18 = *puVar18 & 0xff000000 |
                           *(uint *)(iVar6 + *(int *)(param_1[1] + 4)) & 0xffffff;
                iVar5 = iVar5 + 0x34;
                puVar7 = (uint *)(iVar6 + *(int *)(param_1[1] + 4));
                uVar21 = *puVar7;
                puVar19 = puVar18 + 0xd;
                puVar10 = puVar18;
LAB_8003568c:
                *puVar7 = uVar21 & 0xff000000 | (uint)puVar10 & 0xffffff;
                puVar18 = puVar19;
              }
            }
            puVar16 = puVar16 + 0xe;
            iVar11 = iVar11 + -1;
            puVar22 = puVar22 + 0xe;
          } while (iVar11 != -1);
        }
      }
      iVar3 = iVar3 + 8;
      DAT_800ff5c4 = puVar18;
    }
    else {
      puVar16 = puVar22 + 0xd;
      uVar1 = _DAT_1f8003b0;
      while( true ) {
        uVar21 = uVar21 - 1;
        if (uVar21 == 0xffffffff) break;
        _DAT_1f8003b0 = CONCAT22(DAT_1f8003b0_2,uVar1);
        psVar15 = (short *)((uint)puVar16[-6] * 8 + iVar20);
        psVar14 = (short *)((uint)puVar16[-4] * 8 + iVar20);
        psVar13 = (short *)((uint)puVar16[-2] * 8 + iVar20);
        psVar12 = (short *)((uint)*puVar16 * 8 + iVar20);
        iVar25 = (int)*psVar15 + (int)*psVar14 + (int)*psVar13 + (int)*psVar12;
        if (iVar25 < 0) {
          iVar25 = iVar25 + 3;
        }
        iVar11 = (int)psVar15[1] + (int)psVar14[1] + (int)psVar13[1] + (int)psVar12[1];
        iVar25 = iVar25 >> 2;
        if (iVar25 < 0) {
          iVar25 = -iVar25;
        }
        if (iVar11 < 0) {
          iVar11 = iVar11 + 3;
        }
        iVar5 = (int)psVar15[2] + (int)psVar14[2] + (int)psVar13[2] + (int)psVar12[2];
        iVar11 = iVar11 >> 2;
        if (iVar11 < 0) {
          iVar11 = -iVar11;
        }
        if (iVar5 < 0) {
          iVar5 = iVar5 + 3;
        }
        iVar5 = iVar5 >> 2;
        if (iVar5 < 0) {
          iVar5 = -iVar5;
        }
        FUN_800341f8(iVar25,iVar11,iVar5);
        puVar16 = puVar16 + 0xe;
        uVar1 = _DAT_1f8003b0;
      }
      _DAT_1f8003b0 = CONCAT22(DAT_1f8003b0_2,uVar1);
      iVar3 = iVar3 + 8;
    }
  }
  else {
    iVar3 = FUN_8004d260(param_1);
  }
  return iVar3;
}

