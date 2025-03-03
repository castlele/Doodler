const rl = @import("raylib");
const math = @import("math.zig");

pub const Player = struct {
    position: rl.Vector2,
    size: math.Size(i32),

    pub fn init(initialPosition: rl.Vector2, size: math.Size(i32)) Player {
        return .{
            .position = initialPosition,
            .size = size,
        };
    }

    pub fn draw(self: *const Player) void {
        const x: i32 = @as(i32, @intFromFloat(self.position.x));
        const y: i32 = @as(i32, @intFromFloat(self.position.y));
        const w = self.size.width;
        const h = self.size.height;

        rl.drawRectangle(x, y, w, h, rl.Color.red);
    }
};
