/* Analysis pseudo-C, not buildable source. */

int FUN_8007f204(int param_1)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int local_3c;
  
  cVar3 = -0x80;
  cVar7 = -0x80;
  local_3c = 0;
  cVar4 = -0x80;
  if (((param_1 < 0) || (DAT_80095038 <= param_1)) &&
     (param_1 = DAT_8009503c, *(int *)(&DAT_80094edc + DAT_8009503c * 0x30) == 0)) {
    iVar5 = 0;
  }
  else {
    param_1 = param_1 * 0x30;
    iVar5 = param_1 + -0x7ff6b138;
    pbVar10 = *(byte **)(&DAT_80094edc + param_1);
    iVar17 = *(int *)(&DAT_80094ed4 + param_1);
    iVar12 = (int)*(short *)(&DAT_80094ec0 + param_1);
    iVar14 = (int)*(short *)(&DAT_80094ec2 + param_1);
    iVar8 = iVar14 + *(short *)(&DAT_80094ec6 + param_1);
    iVar13 = *(int *)(&DAT_80094ed8 + param_1);
    iVar15 = *(int *)(&DAT_80094ee4 + param_1);
    iVar16 = iVar12 + *(short *)(&DAT_80094ec4 + param_1);
    FUN_80082d88(iVar5);
    for (; (bVar1 = *pbVar10, *pbVar10 != 0 && (iVar17 != 0)); iVar17 = iVar17 + -1) {
      bVar2 = false;
      iVar9 = iVar13;
      pbVar11 = pbVar10;
      if (bVar1 == 0x20) {
LAB_8007f424:
        iVar12 = iVar12 + 8;
        iVar13 = iVar9;
LAB_8007f428:
        if ((iVar16 <= iVar12) && (iVar15 == 0)) {
LAB_8007f43c:
          bVar2 = true;
        }
      }
      else {
        if ((char)bVar1 < '!') {
          if (bVar1 == 9) {
            iVar12 = iVar12 + 0x20;
            goto LAB_8007f428;
          }
          if (bVar1 != 10) goto LAB_8007f398;
          goto LAB_8007f43c;
        }
        if (bVar1 != 0x7e) {
LAB_8007f398:
          bVar1 = *pbVar10;
          if (bVar1 - 0x61 < 0x1a) {
            iVar9 = (char)bVar1 + -0x40;
          }
          else {
            iVar9 = (char)bVar1 + -0x20;
          }
          iVar6 = iVar9;
          if (iVar9 < 0) {
            iVar6 = iVar9 + 0xf;
          }
          *(char *)(iVar13 + 0xc) = ((char)iVar9 + (char)(iVar6 >> 4) * -0x10) * '\b';
          *(char *)(iVar13 + 0xd) = (char)((iVar6 >> 4) << 3);
          *(short *)(iVar13 + 8) = (short)iVar12;
          *(short *)(iVar13 + 10) = (short)iVar14;
          *(char *)(iVar13 + 4) = cVar3;
          *(char *)(iVar13 + 5) = cVar7;
          *(char *)(iVar13 + 6) = cVar4;
          iVar9 = iVar13 + 0x10;
          FUN_80082d48(iVar5,iVar13);
          goto LAB_8007f424;
        }
        pbVar11 = pbVar10 + 1;
        if (*pbVar11 == 99) {
          pbVar11 = pbVar10 + 4;
          cVar3 = pbVar10[2] * '\x10';
          cVar7 = pbVar10[3] * '\x10';
          cVar4 = *pbVar11 * '\x10';
        }
      }
      if (bVar2) {
        if (local_3c < iVar12) {
          local_3c = iVar12;
        }
        iVar14 = iVar14 + 8;
        iVar12 = (int)*(short *)(&DAT_80094ec0 + param_1);
        if (iVar8 <= iVar14) break;
      }
      pbVar10 = pbVar11 + 1;
    }
    if (((&DAT_80094ebf)[param_1] != '\0') &&
       (FUN_80082d48(iVar5,&DAT_80094eb8 + param_1), iVar15 != 0)) {
      *(short *)(&DAT_80094ec4 + param_1) = (short)local_3c - *(short *)(&DAT_80094ec0 + param_1);
      *(short *)(&DAT_80094ec6 + param_1) =
           (short)iVar14 - (*(short *)(&DAT_80094ec2 + param_1) + -8);
    }
    FUN_80080258(iVar5);
    *(undefined4 *)(&DAT_80094ee0 + param_1) = 0;
    **(undefined1 **)(&DAT_80094edc + param_1) = 0;
  }
  return iVar5;
}

