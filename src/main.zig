const std = @import("std");
const rl = @import("raylib");

pub fn main() !void {
    rl.initWindow(800, 600, "Doodler");

    defer rl.closeWindow();

    while (!rl.windowShouldClose()) {
        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(rl.Color.white);
        rl.drawText("Hello, World!", 800 / 2, 600 / 2, 32, rl.Color.red);
    }
}
