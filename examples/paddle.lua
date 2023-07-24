speed = 20

function ready()

end

function input(self, event)
    if event == KEY_UP then
        self.y -= speed * get_delta()
    elseif event == KEY_DOWN then
        self.y += speed * get_delta()
    end
end
