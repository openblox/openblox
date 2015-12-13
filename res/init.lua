print("Hello, world!");
local lighting = game:GetService("Lighting");
print(lighting);
print(lighting.Ambient);

print(game.CurrentCamera);
local vp = game.CurrentCamera.Viewport;
print(vp);
print(vp.BackgroundColor);
print(Color3.new(1,0,0));
vp.BackgroundColor = Color3.new(1,0,0);
print(vp.BackgroundColor);

lighting.Ambient = Color3.new(1,0,0);
