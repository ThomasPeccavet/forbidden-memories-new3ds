/* Analysis pseudo-C, not buildable source. */

undefined2
FUN_80082a18(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,int param_6,undefined2 param_7)

{
  undefined2 uVar1;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  local_20 = (undefined2)param_4;
  local_1a = param_7;
  local_1e = (undefined2)param_5;
  if (param_2 == 1) {
    local_1c = (undefined2)(param_6 / 2);
  }
  else if (param_2 < 2) {
    if (param_2 == 0) {
      if (param_6 < 0) {
        param_6 = param_6 + 3;
      }
      local_1c = (undefined2)(param_6 >> 2);
    }
  }
  else if (param_2 == 2) {
    local_1c = (undefined2)param_6;
  }
  FUN_8007ff10(&local_20,param_1);
  uVar1 = FUN_80082ce8(param_2,param_3,param_4,param_5);
  return uVar1;
}

