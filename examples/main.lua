function ready()
    spawn("ball.lua")
    spawn_at("paddle.lua", x=50, y=00)
    spawn_at("paddle.lua", x=750, y=300)
end
