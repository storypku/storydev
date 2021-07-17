#include "cyber/mymath.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(mymath, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;
    m.def("add", &add, "A function which adds two numbers",
    py::arg("i") = 2, py::arg("j") = 3);
}
