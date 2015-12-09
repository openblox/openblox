print("Hello, world!");
local lighting = game:GetService("Lighting");
print(lighting);
print(lighting.Ambient);

print(Instance.new("Camera"));

lighting.Ambient = Color3.new(1,0,0);
