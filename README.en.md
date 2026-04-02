# Qt RPC Framework

## Project Introduction

Qt RPC Framework is a lightweight Remote Procedure Call (RPC) framework implemented in **C++ and Qt**, designed for efficient and concise service invocation in distributed or multi-process systems.

This framework provides a unified invocation interface, allowing developers to call remote services just like local functions, while hiding the complexities of underlying network communication, serialization, connection management, etc.

This repository provides only **pre-compiled binary libraries (e.g., `.so`, `.dll`)** for direct integration into existing projects. Source code is not included.

---

## Key Features

- Built with **Qt C++** for easy integration into Qt projects
- Supports **synchronous RPC calls**
- Supports **service registration and invocation**
- Efficient **serialization and deserialization mechanism**
- Supports **multi-threaded concurrent processing**
- Modular design for easy extension
- Supports Linux / Windows platforms

---

## Typical Use Cases

- Distributed service communication
- Microservices architecture
- Inter-process communication (IPC)
- Device and control system communication
- Backend service invocation framework

---

## Requirements

- C++11 or higher
- Qt 5.x
- Supported operating systems:
  - Linux
  - Windows

---

## Integration Guide

### 1. Download Pre-compiled Libraries

Download the pre-compiled library files for your platform and build environment from the [Releases](https://github.com/Starry-Oceaning/qtrpc/releases) page.

### 2. Install to Qt Directory

Copy the following directories from the downloaded package into your Qt installation directory (e.g., Qt's `5.12.8/gcc_64` or your compiler's corresponding directory):

- `bin/`   - Executable files (including RPC-related tools)
- `lib/`   - Linker libraries
- `include/` - Header files
- `mkspecs/` - Qt module configuration

> **Note**: The `moc` executable in the `bin` directory comes from [qt-moc-rpc](https://github.com/Starry-Oceaning/qt-moc-rpc) and is used to handle meta-object compilation for RPC.

### 3. Use in Your Project

Add the following configuration to your project's `.pro` file:

```qmake
QT += rpc
```
After adding, you can include the RPC module's header files in your code and use its functionality.

## Example Code

### Defining a Service

```cpp
#include "qrpcservice.h" //Include RPC header
QRPC_USE_NAMESPACE  // Use the namespace

class TestService : public QRpcService  // Inherit QRpcService
{
    Q_OBJECT
    Q_RPC_MODULE("TestService")   // Define module name
public:
	Q_INVOKABLE int add(int a, int b) {  //Functions under 'public' need the 'Q_INVOKABLE' keyword
		return a + b;
	}
	
public slots:
	int sub(int a, int b) {
		return a - b;
	}

private slots:
	int mul(int a, int b) {
		return a * b;
	}

};
```
Basic types, most containers, and custom structures are supported. For more examples, please refer to the example directory, which contains relatively complete usage demonstrations.

### Registering a Service
```cpp
#include <QCoreApplication>

#include "qrpcserver.h" //Include RPC header
QRPC_USE_NAMESPACE  // Use the namespace

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestService service; 

    QRpcServer server;
    server.addService(&service);

    bool bOk = server.start(9999,"0.0.0.0");

    return a.exec();
}

```

### Client Invocation

```cpp
#include "qrpcclient.h"  //Include RPC header
QRPC_USE_NAMESPACE  // Use the namespace

QRpcClient client;
client.connectToServer("127.0.0.1", 9999);

QRpcCall call;
call.setModuleName("TestService");
call.setMethodName("add");

QRpcResult<int> result = client.invokeMethod(call, 10, 20);
int nRet = result;
qDebug() << result.error() << result.errorString() << nRet; //nRet = 30

```
Basic types, most containers, and custom structures are supported. For more examples, please refer to the example directory, which contains relatively complete usage demonstrations.
 
## Important Note
Although the interface supports types like QVariant, QVariantMap, and QVariantHash, complex types **(i.e., classes that require QVariant::fromValue to be assigned)** need to be manually registered. Please refer to the examples in the example directory for detailed usage.

> [!WARNING]
> **It is strongly recommended NOT to use types containing QVariant in your provided interfaces**, because you cannot know what type the other party will pass. If they pass a type you haven't registered, it will cause disastrous consequences. If you must use them, please make sure you fully understand how they work.

## License

This project is licensed under the **Binary Software License**。

- This repository provides only **binary files**
- Source code is not provided
- Reverse engineering, modification, or redistribution is prohibited

Please see the `LICENSE` file for detailed license terms.

---

## Disclaimer

This software is provided **"AS IS"**, without any express or implied warranties, including but not limited to the warranties of merchantability, fitness for a particular purpose, or non-infringement.

In no event shall the authors or copyright holders be liable for any damages arising from the use of or inability to use this software.

---

## Contact

If you have any questions or suggestions, please contact the author by submitting an Issue.
