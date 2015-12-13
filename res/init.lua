print("Hello, world!");
local lighting = game:GetService("Lighting");
print(lighting);
print(lighting.Ambient);

print(game.Camera);
print(game.CurrentCamera.Viewport);

lighting.Ambient = Color3.new(1,0,0);
