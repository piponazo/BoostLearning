from conans import ConanFile
from conans.tools import os_info

class StingTesting(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'
    # TODO: Try with other generator

    def configure(self):
        self.options['boost'].shared = False

    def requirements(self):
        # Check if we could use boost 1.76 with UR
        self.requires('boost/1.77.0')

    def imports(self):
        self.copy('*.dll', dst='bin', src='bin')

