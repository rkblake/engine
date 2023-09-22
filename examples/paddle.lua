speed = 20
xpos = 10
ypos = 10

function ready()
    
end

function update(self, delta)
    draw_rect(xpos, ypos, 25, 200)
end

function input(self, event)
    if event == KEY_UP then
        self.y -= speed * get_delta()
    elseif event == KEY_DOWN then
        self.y += speed * get_delta()
    end
end
