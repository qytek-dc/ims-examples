#ifndef __IMS_CONNECTION_H__
#define __IMS_CONNECTION_H__

#include <ims/ConnectionList.h>
#include <vector>
#include <memory>

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
std::vector < iMS::IMSSystem > IMSConnection::fullList = std::vector < iMS::IMSSystem > ();

#endif