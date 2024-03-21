const std = @import("std");

pub fn build(b: *std.Build) void {
    const optimization = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const exe = b.addExecutable(.{ .name = "hello", .optimize = optimization, .target = target });
    exe.linkLibC();
    exe.addCSourceFiles(.{ .files = &.{"src/main.c", "src/engine/render.c", "src/engine/render_init.c", "src/io/io.c", "src/global_state.c", "src/engine/render_util.c"}, .flags = &.{ "-std=gnu2x", "-O2", "-Wall", "-Wextra", "-Wpedantic", "-Wno-unused-parameter", "-Wno-gnu", "-Wno-fixed-enum-extension" } });
    exe.addIncludePath(.{ .path = "lib/" });
    exe.linkSystemLibrary("SDL2");
    exe.linkFramework("OpenGL");
    exe.linkSystemLibrary("glfw3");
    exe.linkSystemLibrary("SDL2_image");
    exe.linkSystemLibrary("cglm");
    exe.linkSystemLibrary("m");
    b.installArtifact(exe);

    // This *creates* a Run step in the build graph, to be executed when another
    // step is evaluated that depends on it. The next line below will establish
    // such a dependency.

    const run_cmd = b.addRunArtifact(exe);

    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    // This is not necessary, however, if the application depends on other installed
    // files, this ensures they will be present and in the expected location.
    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);

    // Creates a step for unit testing. This only builds the test executable
    // but does not run it.
    const unit_tests = b.addTest(.{
        .root_source_file = .{ .path = "src/main.c" },
        .target = target,
        .optimize = optimization,
    });

    const run_unit_tests = b.addRunArtifact(unit_tests);

    // Similar to creating the run step earlier, this exposes a `test` step to
    // the `zig build --help` menu, providing a way for the user to request
    // running the unit tests.
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_unit_tests.step);
}
