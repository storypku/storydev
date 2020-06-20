"""Load the vtk library, used by Apollo."""

def repo():
    native.new_local_repository(
        name = "vtk",
        build_file = "third_party/vtk/vtk.BUILD",
        path = "/usr/include/vtk-7.1",
    )
