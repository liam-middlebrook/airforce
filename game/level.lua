local player = factory:createPlayer(vec2(0, 30))

scene:add(player);

local rock_points =
{
    vec2(-5, -5),
    vec2(5, -5),
    vec2(10, 0),
    vec2(0, 20),
    vec2(-10, 0)
};

for x = -500, 500, 50 do
    for y = -500, 500, 50 do
        local rock = factory:createRock(vec2(x, y), rock_points);
        scene:add(rock);
    end
end
