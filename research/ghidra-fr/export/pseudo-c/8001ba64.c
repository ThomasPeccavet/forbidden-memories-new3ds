/* Analysis pseudo-C, not buildable source. */

void FUN_8001ba64(void)

{
  undefined1 uVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  undefined1 auStack_43 [11];
  char local_38 [8];
  undefined4 local_30;
  undefined2 local_2c;
  
  iVar8 = 0;
  do {
    pcVar7 = local_38 + iVar8;
    iVar4 = DAT_8009c500 + iVar8;
    iVar8 = iVar8 + 1;
    *pcVar7 = *(char *)(iVar4 + 0x1a);
  } while (iVar8 < 5);
  pbVar5 = &DAT_800ec210;
  iVar8 = 0;
  do {
    uVar9 = (uint)*pbVar5;
    if (uVar9 == 0) break;
    if (uVar9 < 0x10) {
      auStack_43[uVar9] = 0xff;
    }
    iVar4 = iVar8 + 1;
    pbVar5 = &DAT_800ec211 + iVar8;
    iVar8 = iVar4;
  } while (iVar4 < 5);
  pbVar5 = &DAT_800ec210;
  do {
    uVar9 = (uint)*pbVar5;
    if (uVar9 == 0) {
      return;
    }
    if (0xf < uVar9) {
      iVar8 = 0;
      piVar11 = &DAT_800eb2b8;
      do {
        iVar4 = (int)local_38[iVar8];
        if (-1 < iVar4) {
          iVar10 = iVar4 * 6;
          bVar2 = (&DAT_801ab00b)[uVar9 * 0xc];
          uVar1 = (&DAT_801a7e22)[iVar10];
          iVar6 = (uint)bVar2 * 6;
          (&DAT_801a7e22)[iVar10] = (&DAT_801a7e22)[iVar6];
          (&DAT_801a7e22)[iVar6] = uVar1;
          uVar9 = (uint)DAT_8009c504;
          local_30 = *(undefined4 *)(&DAT_801a7e20 + iVar4 * 3);
          local_2c = *(undefined2 *)(&DAT_801a7e24 + iVar10);
          uVar3 = *(undefined2 *)(&DAT_801a7e24 + iVar6);
          *(undefined4 *)(&DAT_801a7e20 + iVar4 * 3) =
               *(undefined4 *)(&DAT_801a7e20 + (uint)bVar2 * 3);
          *(undefined2 *)(&DAT_801a7e24 + iVar10) = uVar3;
          *(undefined4 *)(&DAT_801a7e20 + (uint)bVar2 * 3) = local_30;
          *(undefined2 *)(&DAT_801a7e24 + iVar6) = local_2c;
          bVar2 = (&DAT_800919d4)[iVar8 + uVar9 * 5];
          iVar6 = *piVar11;
          FUN_80024a9c((uint)bVar2,(int)(char)(&DAT_801a7e22)[iVar10]);
          iVar4 = FUN_80017f94(&DAT_801a7ad8 + (uint)bVar2 * 7,(int)*(short *)(iVar6 + 0x30),
                               (int)*(short *)(iVar6 + 0x32));
          *piVar11 = iVar4;
          FUN_80040690(iVar6);
          *(undefined1 *)(DAT_8009c500 + iVar8 + 0x1a) = (&DAT_801a7e22)[iVar10];
          *pbVar5 = (char)iVar8 + 0xb;
          local_38[iVar8] = -1;
          break;
        }
        iVar8 = iVar8 + 1;
        piVar11 = piVar11 + 3;
      } while (iVar8 < 5);
    }
    pbVar5 = pbVar5 + 1;
    if (-0x7ff13dec < (int)pbVar5) {
      return;
    }
  } while( true );
}

