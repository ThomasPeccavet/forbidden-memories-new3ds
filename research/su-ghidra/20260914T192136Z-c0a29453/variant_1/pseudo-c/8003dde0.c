/* Analysis pseudo-C, not buildable source. */

void FUN_8003dde0(void)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  
  iVar3 = (uint)DAT_8009c769 * 0x268;
  piVar9 = (int *)(&DAT_800f0cec + iVar3);
  if (((DAT_8009c758 & 0x2000) != 0) && (0 < DAT_8009c7b4)) {
    iVar8 = 1;
    do {
      bVar1 = iVar8 < DAT_8009c7b4;
      iVar8 = iVar8 + 1;
    } while (bVar1);
  }
  iVar8 = -1;
  if ((DAT_8009c758 & 0x4000) != 0) {
    iVar8 = FUN_80044cf4(1,&DAT_8009c774,&DAT_8009c744);
  }
  uVar2 = DAT_800f0ce6;
  if ((((DAT_8009c758 & 0x1000) != 0) && (iVar8 != 0)) && (iVar8 == 1)) {
    switch(DAT_8009c774) {
    case 2:
      uVar2 = DAT_8009c758 | 0x2000;
      if (DAT_8009c744 != 1) {
        if (DAT_8009c744 < 2) {
          DAT_8009c758 = uVar2;
          if (DAT_8009c744 == 0) {
LAB_8003df3c:
            (&DAT_800f0cf8)[iVar3] = DAT_8009c7d4;
            goto LAB_8003e038;
          }
        }
        else {
          if (DAT_8009c744 == 3) {
            DAT_8009c758 = DAT_8009c758 | 0x2800;
            goto LAB_8003df3c;
          }
          if (DAT_8009c744 == 4) {
            DAT_8009c758 = DAT_8009c758 | 0x2002;
            DAT_8009c760 = '\x01';
            break;
          }
        }
      }
      DAT_8009c760 = '\x02';
      DAT_8009c758 = uVar2;
      break;
    case 3:
      if (DAT_8009c744 == 0) {
        iVar4 = (uint)DAT_800f0ce2 - (int)(short)DAT_800f0ce6;
        DAT_800f0ce2 = (ushort)iVar4;
        if (iVar4 * 0x10000 < 1) goto LAB_8003e038;
        iVar4 = *piVar9 + (int)(short)DAT_800f0ce6;
LAB_8003dfe8:
        *piVar9 = iVar4;
        DAT_800f0ce4 = DAT_800f0ce4 + uVar2;
        if ((short)DAT_800f0ce2 < (short)DAT_800f0ce6) {
          DAT_800f0ce6 = DAT_800f0ce2;
        }
      }
      else {
LAB_8003e018:
        DAT_8009c760 = '\x01';
      }
      break;
    case 4:
      if (DAT_8009c744 != 0) goto LAB_8003e018;
      iVar4 = (uint)DAT_800f0ce2 - (int)(short)DAT_800f0ce6;
      DAT_800f0ce2 = (ushort)iVar4;
      if (0 < iVar4 * 0x10000) {
        iVar4 = *piVar9 + (int)(short)DAT_800f0ce6;
        goto LAB_8003dfe8;
      }
LAB_8003e038:
      DAT_8009c760 = '\0';
      break;
    case 8:
    case 0xb:
    case 0xc:
      DAT_8009c760 = '\x01';
      if (DAT_8009c744 == 0) goto LAB_8003e038;
    }
  }
  if ((DAT_8009c751 & 0xf) != 0) {
    iVar8 = 1;
    (*(code *)(&PTR_LAB_800923b4)[DAT_8009c751 & 0xf])(&DAT_800f0cd0,piVar9);
  }
  if (-1 < iVar8) {
    return;
  }
  if ((DAT_8009c758 & 0x400) != 0) {
    uVar5 = (uint)DAT_800f0cea;
    FUN_80039770();
    if ((*(uint *)(&DAT_800f0884 + uVar5 * 0x32) & 0x2010) != 0x2000) {
      return;
    }
    DAT_8009c758 = DAT_8009c758 & 0xfbff;
    return;
  }
  switch(DAT_8009c75a & 0xf) {
  case 0:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c751 = 1;
      DAT_8009c75a = DAT_8009c75a | 0x80;
      return;
    }
    if (DAT_8009c6d0 != '\0') {
      DAT_8009c751 = 2;
      return;
    }
    FUN_800442ec(1);
    FUN_80044378();
    DAT_8009c75a = 1;
    DAT_8009c758 = DAT_8009c758 | 0x4000;
  case 1:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      DAT_8009c758 = DAT_8009c758 | 0x1000;
      FUN_800445f8(0);
      return;
    }
    DAT_8009c75a = 4;
  case 4:
    uVar2 = DAT_8009c758 & 0xefff;
    if ((DAT_8009c758 & 0x2000) == 0) {
      return;
    }
    uVar7 = 0xd2;
    DAT_8009c758 = uVar2;
    if (DAT_8009c760 != '\x02') {
      if ((DAT_8009c756 & 1) == 0) {
        DAT_8009c75a = 5;
        return;
      }
      DAT_8009c75a = 7;
      return;
    }
    break;
  default:
    goto switchD_8003e114_caseD_2;
  case 5:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      iVar3 = FUN_80045190(s_BESLES_03948_YUGIOH_80010304);
      if ((-1 < iVar3) && ((DAT_8009c758 & 2) == 0)) {
        iVar3 = *(int *)(iVar3 * 0x28 + DAT_8009c7c0 + 0x20);
        if (iVar3 < 0) {
          iVar3 = iVar3 + 0x3f;
        }
        FUN_80044734(0,0x80210000,iVar3 >> 6);
        return;
      }
      uVar7 = 0xd3;
    }
    else {
      uVar7 = 0xd8;
      if (DAT_8009c760 == '\0') {
        DAT_8009c75a = 6;
        goto switchD_8003e114_caseD_6;
      }
    }
    break;
  case 6:
switchD_8003e114_caseD_6:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      iVar8 = FUN_80045190(s_BESLES_03948_YUGIOH_80010304);
      uVar7 = 0xd3;
      if ((-1 < iVar8) && ((DAT_8009c758 & 2) == 0)) {
        FUN_8003d638(0x80d5,0);
        (&DAT_800f0cf9)[iVar3] = (char)iVar8;
        DAT_8009c758 = DAT_8009c758 | 0x1000;
        FUN_80044698(0,s_BESLES_03948_YUGIOH_80010304,0x80200000,0x200,0x1e00);
        return;
      }
    }
    else {
      uVar7 = 0xd7;
      if (DAT_8009c760 == '\x01') {
        uVar7 = 0xd8;
      }
    }
    break;
  case 7:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      if ((DAT_8009c758 & 2) != 0) {
        DAT_8009c75a = 9;
        return;
      }
      iVar3 = FUN_80045190(s_BESLES_03948_YUGIOH_80010304);
      if (iVar3 < 0) {
        DAT_8009c75a = 10;
        return;
      }
      FUN_8003d638(0x80d6,0);
      FUN_80035ba0(0x80300000,&DAT_801d4000,0x200);
      FUN_80035c48(0x80300200,0x86,0x800);
      FUN_800447a0(0,s_BESLES_03948_YUGIOH_80010304,0x80300000,0,0xa00);
      DAT_8009c758 = DAT_8009c758 | 0x1000;
      return;
    }
    uVar7 = 0xd7;
    if (DAT_8009c760 == '\x01') {
      uVar7 = 0xd9;
    }
    else {
      DAT_8009c75a = 8;
    }
    FUN_8003d638(uVar7,1);
    DAT_8009c758 = DAT_8009c758 | 0x400;
    DAT_8009c75a = 8;
  case 8:
    if ((DAT_8009c75a & 0x80) == 0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      iVar8 = FUN_80045190(s_BESLES_03948_YUGIOH_80010304);
      DAT_8021007f = 0;
      DAT_8021007e = 1;
      DAT_8021007d = 0xff;
      DAT_8021007c = 0xff;
      DAT_8021007b = 0xff;
      DAT_8021007a = 0xff;
      pbVar6 = (byte *)0x80210000;
      iVar3 = 0;
      do {
        iVar4 = iVar3 + 1;
        DAT_8021007f = DAT_8021007f ^ *pbVar6;
        pbVar6 = (byte *)(iVar3 + -0x7fdeffff);
        iVar3 = iVar4;
      } while (iVar4 < 0x7f);
      iVar3 = *(int *)(iVar8 * 0x28 + DAT_8009c7c0 + 0x20);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0x3f;
      }
      FUN_8004483c(0,0x80210000,iVar3 >> 6);
      return;
    }
    uVar7 = 0xd9;
    if (DAT_8009c760 == '\0') {
      return;
    }
    break;
  case 9:
  case 10:
    if ((DAT_8009c75a & 0x80) != 0) {
      return;
    }
    if ((byte)(&DAT_800f0cf8)[iVar3] < DAT_800f0ce0) {
      DAT_8009c75a = DAT_8009c75a | 0x80;
      return;
    }
    DAT_8009c75a = DAT_8009c75a | 0x80;
    FUN_800448a8(0,s_BESLES_03948_YUGIOH_80010304,DAT_800f0ce0);
    return;
  }
  FUN_8003d638(uVar7,1);
  DAT_8009c758 = DAT_8009c758 | 0x400;
switchD_8003e114_caseD_2:
  return;
}

