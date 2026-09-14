/* Analysis pseudo-C, not buildable source. */

void FUN_80017544(void)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined2 local_8 [4];
  
  puVar7 = local_8;
  puVar6 = &DAT_800eb278;
  if (DAT_8009c6f3 < '\0') {
    local_8[0] = DAT_8009c578;
    local_8[1] = DAT_8009c57a;
  }
  else {
    local_8[1] = 8000;
    local_8[0] = 8000;
  }
  iVar8 = 0;
  puVar5 = &DAT_800eb297;
  do {
    iVar3 = 4;
    puVar2 = puVar6 + 4;
    do {
      puVar2[0x1a] = 0xff;
      iVar3 = iVar3 + -1;
      puVar2 = puVar2 + -1;
    } while (-1 < iVar3);
    puVar5[-7] = 0;
    uVar1 = *puVar7;
    uVar4 = 0;
    *(undefined2 *)(puVar5 + -0xd) = 0;
    puVar5[-6] = 0;
    *puVar5 = 0;
    *(undefined2 *)(puVar5 + -0xb) = uVar1;
    *(undefined2 *)(puVar5 + -9) = uVar1;
    puVar2 = puVar6;
    do {
      *puVar2 = 0;
      uVar4 = uVar4 + 1;
      puVar2 = puVar2 + 1;
    } while (uVar4 < 0xd);
    puVar7 = puVar7 + 1;
    iVar8 = iVar8 + 1;
    puVar5 = puVar5 + 0x20;
    puVar6 = puVar6 + 0x20;
  } while (iVar8 < 2);
  if (DAT_8009c6f2 < '\0') {
    if (DAT_8009c6f3 < '\0') {
      DAT_800eb2b7 = DAT_8009c511;
      DAT_800eb297 = DAT_8009c511;
      goto LAB_80017654;
    }
  }
  else if (DAT_8009c6f3 < '\0') goto LAB_80017654;
  DAT_800eb2b7 = 0xff;
LAB_80017654:
  DAT_8009c500 = &DAT_800eb278 + (uint)DAT_8009c504 * 0x20;
  return;
}

