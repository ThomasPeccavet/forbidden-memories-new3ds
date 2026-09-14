/* Analysis pseudo-C, not buildable source. */

void FUN_80087158(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 unaff_retaddr;
  
  if (0x27f < DAT_80096634) {
    DAT_80096628 = unaff_retaddr;
    FUN_8008fa78(s_Error__Can_t_push_matrix_stack_m_800968b8);
    return;
  }
  uVar1 = getCopControlWord(2,0);
  uVar2 = getCopControlWord(2,0x800);
  *(undefined4 *)(&DAT_80096638 + DAT_80096634) = uVar1;
  *(undefined4 *)(&DAT_8009663c + DAT_80096634) = uVar2;
  uVar1 = getCopControlWord(2,0x1000);
  uVar2 = getCopControlWord(2,0x1800);
  *(undefined4 *)(&DAT_80096640 + DAT_80096634) = uVar1;
  *(undefined4 *)(&DAT_80096644 + DAT_80096634) = uVar2;
  uVar1 = getCopControlWord(2,0x2000);
  *(undefined4 *)(&DAT_80096648 + DAT_80096634) = uVar1;
  uVar1 = getCopControlWord(2,0x2800);
  uVar2 = getCopControlWord(2,0x3000);
  uVar3 = getCopControlWord(2,0x3800);
  *(undefined4 *)(&DAT_8009664c + DAT_80096634) = uVar1;
  *(undefined4 *)(&DAT_80096650 + DAT_80096634) = uVar2;
  *(undefined4 *)(&DAT_80096654 + DAT_80096634) = uVar3;
  DAT_80096634 = DAT_80096634 + 0x20;
  return;
}

