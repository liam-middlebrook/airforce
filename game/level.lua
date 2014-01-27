local player = factory:createPlayer(vec2(0, 30))

scene:addObject(player);

local rock_points =
{
    vec2(-5, -5),
    vec2(5, -5),
    vec2(10, 0),
    vec2(0, 20),
    vec2(-10, 0)
};

for x = -1000, 1000, 30 do
    for y = -1000, 1000, 30 do
        local rock = factory:createRock(vec2(x, y), rock_points);
        scene:addObject(rock);
    end
end
