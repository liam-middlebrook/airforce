local function genArc(arr, i, from_x, to_x, step_x, min_y, max_y)
    for x = from_x, to_x, step_x do
         arr[i] = vec2(x, min_y +  math.sin((x - from_x) / (to_x - from_x) * math.pi) * (max_y - min_y));
         i = i + 1;
    end
    return i;
end

local function genTerrain()
    local a = -5000;
    local b = 5000;
    local step = 50;

    local terrain_points = {};
    local terrain_i = 0;

    local holes = {};

    for x = a, b, step do
        local y_min = math.random(-20,0);
        local y_max = math.random(25,50);

        terrain_i = genArc(terrain_points, terrain_i, x, x + 45, 1, y_min, y_max);

        local hole_points = {};
        local hole_i = genArc(hole_points, 0, x + 5, x + 40, 1, y_min, math.random(y_min + 5, y_max - 5));
        genArc(hole_points, hole_i, x + 40, x + 5, -1, y_min - 5, math.random(-40, y_min - 10));

        table.insert(holes, hole_points);
    end

    for x = b, a, -step do
        terrain_i = genArc(terrain_points, terrain_i, x + 45, x, -1, math.random(-40, -25), math.random(-70, -45));
    end

    return terrain_points, holes
end

math.randomseed(os.time());

terrain_points1, holes1 = genTerrain();
terrain_points2, holes2 = genTerrain();

local terrain1 = factory:createTerrain(vec2(0, 0), terrain_points1, holes1);
local terrain2 = factory:createTerrain(vec2(0, 150), terrain_points2, holes2);

scene:addObject(terrain1);
scene:addObject(terrain2);

local rock_points =
{
    vec2(-5, -5),
    vec2(5, -5),
    vec2(10, 0),
    vec2(0, 20),
    vec2(-10, 0)
};

for x = -5000, 5000, 60 do
    local rock = factory:createRock(vec2(x, 65), rock_points);
    scene:addObject(rock);
end

local player = factory:createPlayer(vec2(0, 30))

scene:addObject(player);
