/* Analysis pseudo-C, not buildable source. */

int FUN_8006c74c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined1 auStack_40 [4];
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [4];
  
  FUN_8006c938(auStack_40,param_1);
  FUN_8006c938(auStack_3c,param_2);
  FUN_8006c938(auStack_38,param_3);
  FUN_8006c95c(auStack_34,param_2,param_3);
  FUN_8006c95c(auStack_30,param_3,param_1);
  FUN_8006c95c(auStack_2c,param_1,param_2);
  param_5 = param_5 + -1;
  if (param_5 == 0) {
    FUN_8006c938(param_4,auStack_40);
    FUN_8006c938(param_4 + 4,auStack_2c);
    FUN_8006c938(param_4 + 8,auStack_30);
    FUN_8006c938(param_4 + 0xc,auStack_3c);
    FUN_8006c938(param_4 + 0x10,auStack_34);
    FUN_8006c938(param_4 + 0x14,auStack_2c);
    FUN_8006c938(param_4 + 0x18,auStack_38);
    FUN_8006c938(param_4 + 0x1c,auStack_30);
    FUN_8006c938(param_4 + 0x20,auStack_34);
    FUN_8006c938(param_4 + 0x24,auStack_34);
    FUN_8006c938(param_4 + 0x28,auStack_30);
    FUN_8006c938(param_4 + 0x2c,auStack_2c);
    param_4 = param_4 + 0x30;
  }
  else {
    uVar1 = FUN_8006c74c(auStack_40,auStack_2c,auStack_30,param_4,param_5);
    uVar1 = FUN_8006c74c(auStack_3c,auStack_34,auStack_2c,uVar1,param_5);
    uVar1 = FUN_8006c74c(auStack_38,auStack_30,auStack_34,uVar1,param_5);
    param_4 = FUN_8006c74c(auStack_34,auStack_30,auStack_2c,uVar1,param_5);
  }
  return param_4;
}

