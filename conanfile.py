import shutil

from conan import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = ["catch2/3.4.0", "spdlog/1.12.0"]
    generators = "CMakeDeps"

    def generate(self) -> None:
        ninja_available: bool = shutil.which("ninja") is not None
        generator = "Ninja" if ninja_available else None
        tc = CMakeToolchain(self, generator=generator)
        tc.generate()

    def layout(self) -> None:
        self.folders.source = "src"
        self.folders.build = f"build/{self.settings.build_type}"
        self.folders.generators = f"build/{self.settings.build_type}/generators"

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
