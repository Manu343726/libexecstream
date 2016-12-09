from conans import ConanFile, CMake
import os

class LibExecStream(ConanFile):
    name = "libexecstream"
    url  = "https://github.com/Manu343726/libexecstream"
    license = "http://libexecstream.sourceforge.net/license.html"
    version = "0.3.0"
    settings = "os", "arch", "compiler", "build_type"
    options = { "shared": [True, False] }
    default_options = "shared=True"
    generators = "cmake"
    exports = "include*", "src*", "CMakeLists.txt", "README.md"

    def build(self):
	cmake = CMake(self.settings)

        shared_lib = '-DLIBEXECSTREAM_SHARED=' + 'TRUE' if self.options.shared else 'FALSE'

	self.run('pwd && cmake %s %s %s' % (self.conanfile_directory, cmake.command_line, shared_lib))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dll", dst="lib", keep_path=False)
