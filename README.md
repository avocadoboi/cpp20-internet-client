# c++20 internet client

c++20 internet client is an HTTP/HTTPS client library written in c++20. The library only consists of a single header and source file.

As of now, only gcc supports all of the c++20 features used in this library. Additionally, there are some c++20 features that are not used in the library because no compiler or standard library yet supports them. However the library will be updated over time as compilers start implementing more of c++20.


## Aims and features
* User friendly, functional design.
* An API that is hard to misuse.
* Library code follows c++ core guidelines.
* A single module file when build systems and compilers have good support for modules.
* Support for GET and POST requests, both unsecured and over TLS.
* Support for asynchronous requests.
* Support for Windows, Linux and MacOS.
* Modern CMake integration.

## Simple "GET" request example
Note that the fmt library is not a dependency of this library, it's just to simplify the example.
```cpp
#include <cpp20_internet_client.hpp>
#include <fmt/format.h>

using namespace internet_client;

auto main() -> int {
    try {
        auto const response = http::get("https://www.google.com")
            .add_header({.name="HeaderName", .value="header value"})
            .send();
        fmt::print("Date from server: {}.\n", response.get_header_value("date").value_or("Unknown"));
        response.write_body_to_file("index.html");
    } 
    catch (errors::ConnectionFailed const& error) {
        fmt::print("The connection failed - \"{}\"\n", error.what());
    }
}
```

## Dependencies
The only non-native dependency is OpenSSL on UNIX operating systems. It is recommended to use a package manager like VCPKG to install the OpenSSL libraries, especially on MacOS.  
## Building and installing
You can download, build and install the library as shown below. You only need to do it like this if you want to use the library as an installation as explained later. The information about cmake flags can be useful even if you use the library as a subproject.
```shell
git clone https://github.com/avocadoboi/cpp20-internet-client.git
cd cpp20-internet-client
mkdir build
cmake . -B build
cmake --build build --target cpp20_internet_client
sudo cmake --install build
```
You may want to add some flags to the cmake commands, for example the VCPKG toolchain file or a cmake prefix path for OpenSSL on UNIX systems. Make sure a compiler is used that supports enough of the c++20 features used in the library. For a safe bet, use the latest GCC compiler. On Windows, use for example -G"MinGW Makefiles" or -G"Ninja" instead of the (probably) default visual studio generator if you want to use GCC. Run the command prompt as administrator and remove "sudo" in the last command if you are on Windows.

## Usage
The library exports the target ``Cpp20InternetClient::cpp20_internet_client``. Cpp20InternetClient is the name of the package namespace. There are several ways to include the library in a project.

### Using the installed library
To include the installed library in a CMake project, use find_package like so:
```cmake
find_package(Cpp20InternetClient CONFIG REQUIRED)
target_link_libraries(target_name PRIVATE Cpp20InternetClient::cpp20_internet_client)
```
Where target_name is the name of the target to link the library to.

### Using the library as a subproject
You can clone the library into your own project and then use it like so:
```cmake
add_subdirectory(external/cpp20-internet-client)
target_link_libraries(target_name PRIVATE Cpp20InternetClient::cpp20_internet_client)
```
Where target_name is the name of the target to link the library to. "external/cpp20-internet-client" is just an example of where you could put the library in your project.

### Using CMake to download and include the library
You can use the built-in FetchContent CMake module to directly fetch the repository at configure time and link to it:
```cmake
include(FetchContent)

FetchContent_Declare(
    Cpp20InternetClient
    GIT_REPOSITORY https://github.com/avocadoboi/cpp20-internet-client.git
)
FetchContent_MakeAvailable(Cpp20InternetClient)

target_link_libraries(target_name PRIVATE Cpp20InternetClient::cpp20_internet_client)
```

## Development status
The project is in its initial development and only a subset of the functionality has been implemented.
