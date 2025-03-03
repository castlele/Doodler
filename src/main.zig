const std = @import("std");
const rl = @import("raylib");

const p = @import("player.zig");
const platforms = @import("platforms.zig");

pub fn main() !void {
    const player = p.Player.init(.{
        .x = 400,
        .y = 300,
    }, .{
        .width = 50,
        .height = 50,
    });

    rl.initWindow(800, 600, "Doodler");

    defer rl.closeWindow();

    while (!rl.windowShouldClose()) {
        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(rl.Color.white);
        player.draw();
    }
}
