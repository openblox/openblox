local insts = Instance.listClasses();
for i = 1, #insts do
	print("Instance class: " .. insts[i]);
end

local inst = Instance.new("TestInstance");
print("I made an Instance!");
print(inst);
