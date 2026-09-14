/* Analysis pseudo-C, not buildable source. */

void FUN_80080388(uint param_1,int param_2)

{
  undefined *puVar1;
  
  if (1 < DAT_80095a9a) {
    (*(code *)PTR_FUN_80095a94)(s_DrawOTagEnv__08x__08x_____80012208,param_1,param_2);
  }
  FUN_80080ca8(param_2 + 0x1c,param_2);
  puVar1 = PTR_PTR_80095a90;
  *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) & 0xff000000 | param_1 & 0xffffff;
  (**(code **)(puVar1 + 8))(*(undefined4 *)(puVar1 + 0x18),param_2 + 0x1c,0x40,0);
  FUN_8008f508(&DAT_80095aa8,param_2,0x5c);
  return;
}

