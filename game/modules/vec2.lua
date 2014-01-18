vec2 = {}
vec2.__index = vec2

function vec2.__add(a, b)
    if type(a) == "number" then
        return vec2.new(b.x + a, b.y + a)
    elseif type(b) == "number" then
        return vec2.new(a.x + b, a.y + b)
    else
        return vec2.new(a.x + b.x, a.y + b.y)
    end
end

function vec2.__sub(a, b)
    if type(a) == "number" then
        return vec2.new(b.x - a, b.y - a)
    elseif type(b) == "number" then
        return vec2.new(a.x - b, a.y - b)
    else
        return vec2.new(a.x - b.x, a.y - b.y)
    end
end

function vec2.__mul(a, b)
    if type(a) == "number" then
        return vec2.new(b.x * a, b.y * a)
    elseif type(b) == "number" then
        return vec2.new(a.x * b, a.y * b)
    else
        return vec2.new(a.x * b.x, a.y * b.y)
    end
end

function vec2.__div(a, b)
    if type(a) == "number" then
        return vec2.new(b.x / a, b.y / a)
    elseif type(b) == "number" then
        return vec2.new(a.x / b, a.y / b)
    else
        return vec2.new(a.x / b.x, a.y / b.y)
    end
end

function vec2.__eq(a, b)
    return a.x == b.x and a.y == b.y
end

function vec2.__lt(a, b)
    return a.x < b.x or (a.x == b.x and a.y < b.y)
end

function vec2.__le(a, b)
    return a.x <= b.x and a.y <= b.y
end

function vec2.__tostring(a)
    return "(" .. a.x .. ", " .. a.y .. ")"
end

function vec2.new(x, y)
    return setmetatable({ x = x or 0, y = y or 0 }, vec2)
end

function vec2.distance(a, b)
    return (b - a):len()
end

function vec2:clone()
    return vec2.new(self.x, self.y)
end

function vec2:unpack()
    return self.x, self.y
end

function vec2:len()
    return math.sqrt(self.x * self.x + self.y * self.y)
end

function vec2:lenSq()
    return self.x * self.x + self.y * self.y
end

function vec2:normalize()
    local len = self:len()

    self.x = self.x / len
    self.y = self.y / len

    return self
end

function vec2:normalized()
    return self / self:len()
end

function vec2:rotate(phi)
    local c = math.cos(phi)
    local s = math.sin(phi)

    self.x = c * self.x - s * self.y
    self.y = s * self.x + c * self.y

    return self
end

function vec2:rotated(phi)
    return self:clone():rotate(phi)
end

function vec2:perpendicular()
    return vec2.new(-self.y, self.x)
end

function vec2:cross(other)
    return self.x * other.y - self.y * other.x
end

setmetatable(vec2, { __call = function(_, ...) return vec2.new(...) end })
