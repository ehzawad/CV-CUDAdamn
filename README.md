# CV-CUDA

[![License](https://img.shields.io/badge/License-Apache_2.0-yellogreen.svg)](https://opensource.org/licenses/Apache-2.0)

![Version](https://img.shields.io/badge/Version-v0.3.0--beta-blue)

![Platform](https://img.shields.io/badge/Platform-linux--64_%7C_win--64_wsl2-gray)

[![Cuda](https://img.shields.io/badge/CUDA-v11.7-%2376B900?logo=nvidia)](https://developer.nvidia.com/cuda-toolkit-archive)
[![GCC](https://img.shields.io/badge/GCC-v11.0-yellow)](https://gcc.gnu.org/gcc-11/changes.html)
[![Python](https://img.shields.io/badge/python-v3.7_%7c_v3.8_%7c_v3.9_%7c_v3.10-blue?logo=python)](https://www.python.org/)
[![CMake](https://img.shields.io/badge/CMake-v3.22-%23008FBA?logo=cmake)](https://cmake.org/)

CV-CUDA is an open-source project that enables building efficient cloud-scale
Artificial Intelligence (AI) imaging and computer vision (CV) applications. It
uses graphics processing unit (GPU) acceleration to help developers build highly
efficient pre- and post-processing pipelines. CV-CUDA originated as a
collaborative effort between [NVIDIA][NVIDIA Develop] and [ByteDance][ByteDance].

Refer to our [Developer Guide](DEVELOPER_GUIDE.md) for more information on the
operators available as of release v0.3.0-beta.

## Getting Started

To get a local copy up and running follow these steps.

### Pre-requisites

- Linux distro:
  - Ubuntu x86_64 == 18.04, 20.04, 22.04
  - WSL2 with Ubuntu >= 20.04 (https://docs.nvidia.com/cuda/wsl-user-guide/index.html)
- NVIDIA driver >= 515.43.04+
- CUDA Toolkit >= 11.7
  - Toolkit >= 11.3 support for core library build and run
- GCC >= 11.0
  - GCC >= 9.0 supported for core library build and run
- Python == 3.7, 3.8, 3.10
- cmake >= 3.22

### Installation

The following steps describe how to install CV-CUDA from pre-built install
packages. Choose the installation method that meets your environment needs.

#### Tar File Installation

```shell
tar -xvf nvcv-lib-0.3.0-cuda11-x86_64-linux.tar.xz
tar -xvf nvcv-dev-0.3.0-cuda11-x86_64-linux.tar.xz
```

#### DEB File Installation

```shell
sudo apt-get install -y ./nvcv-lib-0.3.0-cuda11-x86_64-linux.deb ./nvcv-dev-0.3.0-cuda11-x86_64-linux.deb
```

#### Python WHL File Installation

```shell
pip install nvcv_python-0.3.0-cp38-cp38-linux_x86_64.whl
```

### Build from Source

Follow these instruction to build CV-CUDA from source:

1. Set up your local CV-CUDA repository

    1. Install prerequisites needed to setup up the repository.

       On Ubuntu 22.04, install the following packages:
       - git-lfs: to retrieve binary files from remote repository

       ```shell
       sudo apt-get install -y git git-lfs
       ```

    2. After cloning the repository (assuming it was cloned in `~/cvcuda`),
       it needs to be properly configured by running the `init_repo.sh` script only once.

       ```shell
       cd ~/cvcuda
       ./init_repo.sh
       ```

1. Build CV-CUDA

    1. Install the dependencies required for building CV-CUDA

       On Ubuntu 22.04, install the following packages:
       - g++-11: compiler to be used
       - cmake, ninja-build (optional): manage build rules
       - python3-dev: for python bindings
       - libssl-dev: needed by the testsuite (MD5 hashing utilities)

       ```shell
       sudo apt-get install -y g++-11 cmake ninja-build python3-dev libssl-dev
       ```

       For CUDA Toolkit, any version of the 11.x series should work.
       CV-CUDA was tested with 11.7, thus it should be preferred.

       ```shell
       sudo apt-get install -y cuda-minimal-build-11-7
       ```

    2. Build the project

       ```shell
       ci/build.sh
       ```

       This will compile a x86 release build of CV-CUDA inside `build-rel` directory.
       The library is in build-rel/lib, docs in build-rel/docs and executables
       (tests, etc...) are in build-rel/bin.

       The script accepts some parameters to control the creation of the build tree:

       ```shell
       ci/build.sh [release|debug] [output build tree path]
       ```

       By default it builds for release.

       If output build tree path isn't specified, it'll be `build-rel` for release
       builds, and `build-deb` for debug.

1. Build Documentation

    1. Install the dependencies required for building the documentation

       On Ubuntu 22.04, install the following packages:
       - doxygen: parse header files for reference documentation
       - python3, python3-pip: to install some python packages needed
       - sphinx, breathe, exhale, recommonmark, graphiviz: to render the documentation
       - sphinx-rtd-theme: documenation theme used

       ```shell
       sudo apt-get install -y doxygen graphviz python3 python3-pip
       sudo python3 -m pip install sphinx==4.5.0 breathe exhale recommonmark graphviz sphinx-rtd-theme
       ```

    2. Build the documentation
       ```shell
       ci/build_docs.sh [build folder]
       ```

       Example:
       `ci/build_docs.sh build_docs`

1. Build and run Samples

   1. For instructions on how to build samples from source and run them, see the [Samples](samples/README.md) documentation.

1. Run Tests

   1. Install the dependencies required for running the tests

       On Ubuntu 22.04, install the following packages:
       - python3, python3-pip: to run python bindings tests
       - torch: dependencies needed by python bindings tests

       ```shell
       sudo apt-get install -y python3 python3-pip
       sudo python3 -m pip install pytest torch
       ```

   2. Run the tests

       The tests are in `<buildtree>/bin`. You can run the script below to run all
       tests at once. Here's an example when build tree is created in `build-rel`

       ```shell
       build-rel/bin/run_tests.sh
       ```

1. Package installers

   Installers can be generated using the following cpack command once you have successfully built the project

   ```shell
   cd build-rel
   cpack .
   ```

   This will generate in the build directory both Debian installers and tarballs
   (\*.tar.xz), needed for integration in other distros.

   For a fine-grained choice of what installers to generate, the full syntax is:

   ```shell
   cpack . -G [DEB|TXZ]
   ```

   - DEB for Debian packages
   - TXZ for \*.tar.xz tarballs.

## Tools

1. CV-CUDA make operator tool

   This tool will create an noop operator; python bindings, and tests.

   This tool is located in 'tools/mkop'. To run it, navigate to the directory and execute the command './mkop.sh OperatorName', where 'OperatorName' is the desired name of the operator.

## Contributing

CV-CUDA is an open source project. As part of the Open Source Community, we are
committed to the cycle of learning, improving, and updating that makes this
community thrive. However, as of release v0.3.0-beta, CV-CUDA is not yet ready
for external contributions.

To understand the process for contributing the CV-CUDA, see our
[Contributing](CONTRIBUTING.md) page. To understand our committment to the Open
Source Community, and providing an environment that both supports and respects
the efforts of all contributors, please read our
[Code of Conduct](CODE_OF_CONDUCT.md).

## License

CV-CUDA operates under the [Apache-2.0](LICENSE.md) license.

## Security

CV-CUDA, as a NVIDIA program, is committed to secure development practices.
Please read our [Security](SECURITY.md) page to learn more.

## Acknowledgements

CV-CUDA is developed jointly by NVIDIA and ByteDance.

[NVIDIA Develop]: https://developer.nvidia.com/
[ByteDance]: https://www.bytedance.com/
