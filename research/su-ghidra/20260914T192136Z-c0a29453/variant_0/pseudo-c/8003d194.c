/* Analysis pseudo-C, not buildable source. */

void FUN_8003d194(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  DAT_8009c2ec._0_2_ = FUN_8003d084(param_1 + 0x400,0x204);
  puVar3 = (undefined4 *)(param_1 + 0x624);
  iVar2 = 8;
  *(undefined2 *)(param_1 + 0x606) = (undefined2)DAT_8009c2ec;
  *(undefined2 *)(param_1 + 0x604) = (undefined2)DAT_8009c2ec;
  DAT_8009c2ec._2_1_ = (char)(undefined2)DAT_8009c2ec;
  DAT_8009c2ec._3_1_ = (char)((ushort)(undefined2)DAT_8009c2ec >> 8);
  s_UUUU__8009c2f0._0_4_ = DAT_8009c2ec;
  do {
    iVar2 = iVar2 + -1;
    uVar1 = FUN_8003d040();
    *puVar3 = uVar1;
    puVar3 = puVar3 + -1;
  } while (iVar2 != 0);
  return;
}

