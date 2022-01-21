# Example 02: Scanning For an iMS System

In example 1, we set up a simple CMake project that linked to the iMS control library and saw how CMake could be used to build iMS applications with just a few lines of C++ code.

Let's build on this example to search for and connect to some iMS hardware.

You will, of course, need some Isomet iMS hardware.  In this example, we will assume you have an iMS4-P rev C on hand and connected through Ethernet.  There are other models available within the range but these basic steps are always the same.

Select the [ims-example-02] target in the status bar of VS Code then follow the steps from example 01 to build and run the example.

![Example 02 Output](/images/ims-example-02-output.png)

The example scans all of the supported and enabled interfaces and reports the details of all of the iMS systems that it discovers to the user who is prompted to make a choice.

Having chosen an iMS system, the example connects to it, reads back some system information to display, then disconnects and exits.  If you don't get a similar output to the above, refer to [Not Working?](#not-working) below.

---

## IMSConnection Class and iMS::ConnectionList

iMS::ConnectionList is the most important class within the iMS control library and is likely to be the first that you need to use and understand.

It contains all of the procedures for communicating with an iMS system on any interface, maintaining a list of all the messages that are sent and received, transferring bulk data in the background and connecting event triggers to event handlers.

It is essential that a single instance of ConnectionList is created and it must remain alive (not destroyed) for the duration of the required connection, usually that is when the program exits.

Because it is so important, it is worth writing a wrapper class around it to guarantee its lifetime and to simplify its use with the rest of the program.  In this example, I have called the wrapper class `IMSConnection`:

```cpp
class IMSConnection {
public:
    IMSConnection() {}

    static void Scan() { fullList = _imsconn->scan(); }
    std::vector < iMS::IMSSystem >& List() { return fullList; }

private:
    IMSConnection(const IMSConnection&); // non-copyable
    const IMSConnection& operator =(const IMSConnection&);  // non-assignable

    static std::unique_ptr < iMS::ConnectionList > _imsconn;
    static std::vector < iMS::IMSSystem > fullList;
};

std::unique_ptr < iMS::ConnectionList > IMSConnection::_imsconn = std::make_unique < iMS::ConnectionList> ();
```

The wrapper class initialises a unique_ptr to `iMS::ConnectionList` which is created at object construction and is shared by all instances of `IMSConnection`.  The static function `Scan` wraps around the library scan function and populates the list of iMS Systems which can be returned by `List()`.

A single object of this wrapper is made globally in the example:

```cpp
IMSConnection conn;
```

together with a pointer to the iMS system that we will connect to, which is declared uninitialised:

```cpp
iMS::IMSSystem * myiMS = nullptr ;
```

In our example code, we first call the `Scan` function, wait for the results (this can take a number of seconds), then display the list of systems to the user, prompting them to choose one:

```cpp
    conn.Scan();
```

If any systems are discovered, they will exist in the static vector called `fullList` in the wrapper, so we will set our hardware pointer to one of them:

```cpp
    myiMS = &conn.List().at(i-1);
```

`myiMS` can then be used throughout the program to interact with the iMS hardware, safe from harm because our IMSConnection object upholds the lifetime of the connection through until the program exits.

---

## Not working?

The library is doing a lot of work 'behind the scenes.'  If you are unable to connect to iMS hardware and you are using an Ethernet connection, try the following to fix the problem:

* Check what IP address the iMS hardware is using.  By default, iMS systems ship with DHCP enabled to obtain an address from a network DHCP server, however they can also be configured for a fixed IP address.  There is a Windows utility 'iMS IP Config' which can connect to the iMS over USB to find out its current IP address assignment and also to switch between DHCP and fixed IP modes.

* Can you 'ping' the iMS system from the development machine?  iMS systems and the example application need to either be on the same subnet as each other or on a network with correctly configured routing tables

* Do you have a firewall enabled?  Try allowing the example application through the system firewall or opening ports 28243/UDP and 28245/TCP.

* The software uses a proprietary discovery protocol which broadcasts a discovery packet on the physical network interfaces of the development system.  In some cases, particularly if using virtualisation/VMs, this can fail because the system the software is running on is isolated from the host system's network by NAT and the broadcast packets are unable to propagate to the host network.  Try changing the Virtual Machine's network adapter from NAT to Bridged mode.
