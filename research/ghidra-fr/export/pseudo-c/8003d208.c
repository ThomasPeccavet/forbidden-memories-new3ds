/* Analysis pseudo-C, not buildable source. */

void FUN_8003d208(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  FUN_80035ba0(param_1,&DAT_801d4000,0x200);
  cVar2 = DAT_8009c784;
  uVar1 = DAT_8009c41c;
  *(undefined4 *)(param_1 + 0x600) = 0;
  *(undefined4 *)(param_1 + 0x608) = uVar1;
  if (cVar2 < '\0') {
    DAT_8009c784 = '\0';
  }
  *(char *)(param_1 + 0x7de) = DAT_8009c784;
  iVar3 = DAT_8009c73c + 1;
  *(int *)(param_1 + 0x604) = iVar3;
  *(int *)(param_1 + 0xc84) = iVar3;
  FUN_8003d0e0(param_1 + 0x200);
  FUN_8003d194(param_1 + 0x200);
  uVar4 = 0;
  iVar3 = param_1;
  do {
    *(undefined1 *)(iVar3 + 0x828) = 0;
    uVar4 = uVar4 + 1;
    iVar3 = param_1 + uVar4;
  } while (uVar4 < 0x58);
  FUN_80035ba0(param_1 + 0x880,param_1 + 0x200,0x680);
  return;
}

