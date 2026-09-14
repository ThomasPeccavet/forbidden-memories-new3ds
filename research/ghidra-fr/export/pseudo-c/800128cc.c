/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x800129ac) */

void entry_fr(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 unaff_s0;
  undefined4 unaff_s1;
  uint uVar3;
  undefined4 unaff_retaddr;
  undefined4 uVar4;
  
  puVar2 = &DAT_8009c408;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_800ffc30);
  uVar3 = DAT_8009c2a0 - 8U | 0x80000000;
  DAT_800918f0 = ((DAT_8009c2a0 - 8U) - DAT_8009c2a4) + -0xffc30;
  DAT_800918ec = &DAT_800ffc30;
  uVar4 = 0x80012968;
  DAT_8009c408 = unaff_retaddr;
  startup_candidate_fr();
  iVar1 = DAT_800918e8;
  trap(1);
  *(undefined4 *)(uVar3 - 0xc) = unaff_s0;
  *(undefined4 *)(uVar3 - 8) = unaff_s1;
  *(undefined4 *)(uVar3 - 4) = uVar4;
  if (iVar1 == 0) {
    DAT_800918e8 = 1;
  }
  return;
}

