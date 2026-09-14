/* Analysis pseudo-C, not buildable source. */

void FUN_800871fc(void)

{
  int iVar1;
  undefined4 unaff_retaddr;
  
  iVar1 = DAT_80096634;
  if (DAT_80096634 < 1) {
    DAT_80096628 = unaff_retaddr;
    FUN_8008fa78(s_Error__Can_t_pop_matrix_stack_is_800968e9);
    return;
  }
  DAT_80096634 = DAT_80096634 + -0x20;
  setCopControlWord(2,0,*(undefined4 *)(&DAT_80096618 + iVar1));
  setCopControlWord(2,0x800,*(undefined4 *)(&DAT_8009661c + iVar1));
  setCopControlWord(2,0x1000,*(undefined4 *)(&DAT_80096620 + iVar1));
  setCopControlWord(2,0x1800,*(undefined4 *)(&DAT_80096624 + iVar1));
  setCopControlWord(2,0x2000,*(undefined4 *)((int)&DAT_80096628 + iVar1));
  setCopControlWord(2,0x2800,*(undefined4 *)(&DAT_8009662c + iVar1));
  setCopControlWord(2,0x3000,*(undefined4 *)(&DAT_80096630 + iVar1));
  setCopControlWord(2,0x3800,*(undefined4 *)((int)&DAT_80096634 + iVar1));
  return;
}

