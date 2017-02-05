local red = Color3.new(1, 0, 0);

local lighting = game:GetService("Lighting");

print("Red: " .. tostring(red));

print("FogStart");
lighting.FogStart = 10;
print("FogEnd");
lighting.FogEnd = 100;
print("FogColor");
lighting.FogColor = red;
print("FogEnabled");
lighting.FogEnabled = true;
