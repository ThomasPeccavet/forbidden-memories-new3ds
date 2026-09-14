/* Analysis pseudo-C, not buildable source. */

void FUN_8008cffc(int param_1,undefined4 *param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  
  uVar3 = DAT_80012535;
  uVar2 = DAT_80012534;
  *param_2 = DAT_80012530;
  *(undefined1 *)(param_2 + 1) = uVar2;
  *(undefined1 *)((int)param_2 + 5) = uVar3;
  iVar4 = param_1;
  if (param_1 < 0) {
    iVar4 = param_1 + 0xf;
  }
  cVar1 = (char)(iVar4 >> 4);
  *(char *)((int)param_2 + 2) = cVar1 + '0';
  *(char *)((int)param_2 + 3) = (char)param_1 + cVar1 * -0x10 + '0';
  return;
}

