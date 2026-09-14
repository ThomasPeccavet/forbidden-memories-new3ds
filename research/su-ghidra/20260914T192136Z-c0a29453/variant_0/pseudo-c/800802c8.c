/* Analysis pseudo-C, not buildable source. */

int FUN_800802c8(int param_1)

{
  undefined *puVar1;
  
  if (1 < DAT_80095a9a) {
    (*(code *)PTR_FUN_80095a94)(s_PutDrawEnv__08x_____800121f0,param_1);
  }
  FUN_80080ca8(param_1 + 0x1c,param_1);
  puVar1 = PTR_PTR_80095a90;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0xffffff;
  (**(code **)(puVar1 + 8))(*(undefined4 *)(puVar1 + 0x18),param_1 + 0x1c,0x40,0);
  FUN_8008f508(&DAT_80095aa8,param_1,0x5c);
  return param_1;
}

