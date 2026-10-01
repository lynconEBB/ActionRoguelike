import os
import subprocess
import sys
from pathlib import Path

is_linux = sys.platform == "linux"
default_unreal_dir = "/opt/unreal-engine" if is_linux else "C:/Program Files/Epic Games/UE_5.8"
unreal_dir = Path(os.environ.get("UE_DIR", default_unreal_dir))

if (is_linux):
    build_script = unreal_dir / "Engine/Build/BatchFiles/Linux/Build.sh"
    ubt_script = unreal_dir / "Engine/Build/BatchFiles/RunUBT.sh"
    unreal_editor = unreal_dir / "Engine/Binaries/Linux/UnrealEditor"
else:
    build_script = unreal_dir / "Engine/Build/BatchFiles/Build.bat"
    ubt_script = build_script
    unreal_editor = unreal_dir / "Engine/Binaries/Win64/UnrealEditor.exe"

project_root = Path(__file__).resolve().parent
uproject_files = list(project_root.glob("*.uproject"))
assert len(uproject_files) == 1, "Expected exactly one .uproject file on root!"
uproject_file = uproject_files[0]
project_name = uproject_file.stem

def build(arguments):
    subprocess.run(
        [
            build_script,
            f"{project_name}Editor",
            "Linux" if is_linux else "Win64",
            "Development",
            f"-Project={uproject_file}",
            "-WaitMutex",
            "-NoHotReload",
            *arguments,
        ],
        check=True,
    )
    subprocess.run(
        [
            ubt_script,
            f"{project_name}Editor",
            "Linux" if is_linux else "Win64",
            "Development",
            "-mode=GenerateClangDatabase",
            f"-Project={uproject_file}",
            f"-OutputDir={project_root}",
        ],
        check=True,
    )

def editor(arguments):
    environment = os.environ.copy()
    if (is_linux):
        adb = (
            Path(environment.get("ANDROID_HOME", Path.home() / "Android/Sdk"))
            / "platform-tools/adb"
        )
        adb_environment = environment.copy()
        adb_environment.pop("ADB_SERVER_SOCKET", None)
        subprocess.run([adb, "start-server"], check=True, env=adb_environment)

        for variable in (
            "QT_SCALE_FACTOR",
            "QT_AUTO_SCREEN_SCALE_FACTOR",
            "GDK_SCALE",
            "GDK_DPI_SCALE",
        ):
            environment.pop(variable, None)
        environment.update(
            {
                "SDL_VIDEODRIVER": "x11",
                "GDK_BACKEND": "x11",
                "QT_QPA_PLATFORM": "xcb",
                "ADB_SERVER_SOCKET": "tcp:127.0.0.1:5037",
            }
        )

        subprocess.run(
            [unreal_editor, uproject_file,  *arguments],
            check=True,
            env=environment,
        )
    else:
        subprocess.Popen(
            [unreal_editor, uproject_file, "-log",  *arguments],
            env=environment,
        )

def uht(arguments):
    platform = "Linux" if is_linux else "Win64"
    subprocess.run(
        [
            ubt_script,
            "-mode=UnrealHeaderTool",
            f"-Target={project_name}Editor {platform} Development -Project={uproject_file}",
            *arguments,
        ],
        check=True,
    )

def main():
    if len(sys.argv) < 2:
        script_name = Path(sys.argv[0]).name
        raise SystemExit(f"Usage: python3 {script_name} <build|editor> [arguments...]")

    command = sys.argv[1]
    arguments = sys.argv[2:]

    if command == "build":
        build(arguments)
    elif command == "editor":
        editor(arguments)
    elif command == "uht":
        uht(arguments)
    else:
        raise SystemExit(f"Unknown command: {command}")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nStopped.", file=sys.stderr)
        raise SystemExit(130) from None
