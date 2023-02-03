# Lab 1: Transformations with Eigen
This is our proposed solution for lab 1 in TEK5030.

Please see the lab guide at https://github.com/tek5030/lab_01.

To install dependencies with conan, follow our [getting started-guide](https://tek5030.github.io/tutorial/conan.html) in the [TEK5030 resource pages](https://tek5030.github.io). After you have successfully installed conan, proceed with the following commands:

- In CLion, `<build folder>` may be either `cmake_build_debug` or `cmake_build_release` depending on your chosen configuration.
- In VS Code, just using `build` as the build folder will suffice.

```bash
cd ~/tek5030/lab_01_solution

conan install . -if <build folder> -b missing
```

Open the project in your editor, and compile the solution.
