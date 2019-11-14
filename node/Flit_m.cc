//
// Generated file, do not edit! Created by nedtool 5.4 from node/Flit.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "Flit_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(Flit)

Flit::Flit(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    for (unsigned int i=0; i<10; i++)
        this->address[i] = 0;
    this->addressLength = 0;
    for (unsigned int i=0; i<1024; i++)
        this->data[i] = 0;
    this->hopes = 0;
    this->type = 0;
    this->type_packet = 0;
    this->sourceId = 0;
    this->destinationId = 0;
    this->size = 0;
    this->uniqueId = 0;
    for (unsigned int i=0; i<7; i++)
        this->sendData[i] = 0;
    for (unsigned int i=0; i<7; i++)
        this->receiveData[i] = 0;
    this->flitCreationTime = 0;
}

Flit::Flit(const Flit& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Flit::~Flit()
{
}

Flit& Flit::operator=(const Flit& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Flit::copy(const Flit& other)
{
    for (unsigned int i=0; i<10; i++)
        this->address[i] = other.address[i];
    this->addressLength = other.addressLength;
    for (unsigned int i=0; i<1024; i++)
        this->data[i] = other.data[i];
    this->hopes = other.hopes;
    this->type = other.type;
    this->type_packet = other.type_packet;
    this->sourceId = other.sourceId;
    this->destinationId = other.destinationId;
    this->size = other.size;
    this->uniqueId = other.uniqueId;
    for (unsigned int i=0; i<7; i++)
        this->sendData[i] = other.sendData[i];
    for (unsigned int i=0; i<7; i++)
        this->receiveData[i] = other.receiveData[i];
    this->flitCreationTime = other.flitCreationTime;
}

void Flit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimArrayPacking(b,this->address,10);
    doParsimPacking(b,this->addressLength);
    doParsimArrayPacking(b,this->data,1024);
    doParsimPacking(b,this->hopes);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->type_packet);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destinationId);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->uniqueId);
    doParsimArrayPacking(b,this->sendData,7);
    doParsimArrayPacking(b,this->receiveData,7);
    doParsimPacking(b,this->flitCreationTime);
}

void Flit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimArrayUnpacking(b,this->address,10);
    doParsimUnpacking(b,this->addressLength);
    doParsimArrayUnpacking(b,this->data,1024);
    doParsimUnpacking(b,this->hopes);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->type_packet);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destinationId);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->uniqueId);
    doParsimArrayUnpacking(b,this->sendData,7);
    doParsimArrayUnpacking(b,this->receiveData,7);
    doParsimUnpacking(b,this->flitCreationTime);
}

unsigned int Flit::getAddressArraySize() const
{
    return 10;
}

int Flit::getAddress(unsigned int k) const
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return this->address[k];
}

void Flit::setAddress(unsigned int k, int address)
{
    if (k>=10) throw omnetpp::cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->address[k] = address;
}

int Flit::getAddressLength() const
{
    return this->addressLength;
}

void Flit::setAddressLength(int addressLength)
{
    this->addressLength = addressLength;
}

unsigned int Flit::getDataArraySize() const
{
    return 1024;
}

int Flit::getData(unsigned int k) const
{
    if (k>=1024) throw omnetpp::cRuntimeError("Array of size 1024 indexed by %lu", (unsigned long)k);
    return this->data[k];
}

void Flit::setData(unsigned int k, int data)
{
    if (k>=1024) throw omnetpp::cRuntimeError("Array of size 1024 indexed by %lu", (unsigned long)k);
    this->data[k] = data;
}

int Flit::getHopes() const
{
    return this->hopes;
}

void Flit::setHopes(int hopes)
{
    this->hopes = hopes;
}

int Flit::getType() const
{
    return this->type;
}

void Flit::setType(int type)
{
    this->type = type;
}

int Flit::getType_packet() const
{
    return this->type_packet;
}

void Flit::setType_packet(int type_packet)
{
    this->type_packet = type_packet;
}

int Flit::getSourceId() const
{
    return this->sourceId;
}

void Flit::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int Flit::getDestinationId() const
{
    return this->destinationId;
}

void Flit::setDestinationId(int destinationId)
{
    this->destinationId = destinationId;
}

int Flit::getSize() const
{
    return this->size;
}

void Flit::setSize(int size)
{
    this->size = size;
}

int Flit::getUniqueId() const
{
    return this->uniqueId;
}

void Flit::setUniqueId(int uniqueId)
{
    this->uniqueId = uniqueId;
}

unsigned int Flit::getSendDataArraySize() const
{
    return 7;
}

int Flit::getSendData(unsigned int k) const
{
    if (k>=7) throw omnetpp::cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    return this->sendData[k];
}

void Flit::setSendData(unsigned int k, int sendData)
{
    if (k>=7) throw omnetpp::cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    this->sendData[k] = sendData;
}

unsigned int Flit::getReceiveDataArraySize() const
{
    return 7;
}

int Flit::getReceiveData(unsigned int k) const
{
    if (k>=7) throw omnetpp::cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    return this->receiveData[k];
}

void Flit::setReceiveData(unsigned int k, int receiveData)
{
    if (k>=7) throw omnetpp::cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    this->receiveData[k] = receiveData;
}

::omnetpp::simtime_t Flit::getFlitCreationTime() const
{
    return this->flitCreationTime;
}

void Flit::setFlitCreationTime(::omnetpp::simtime_t flitCreationTime)
{
    this->flitCreationTime = flitCreationTime;
}

class FlitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    FlitDescriptor();
    virtual ~FlitDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FlitDescriptor)

FlitDescriptor::FlitDescriptor() : omnetpp::cClassDescriptor("Flit", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

FlitDescriptor::~FlitDescriptor()
{
    delete[] propertynames;
}

bool FlitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Flit *>(obj)!=nullptr;
}

const char **FlitDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FlitDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FlitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int FlitDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *FlitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "addressLength",
        "data",
        "hopes",
        "type",
        "type_packet",
        "sourceId",
        "destinationId",
        "size",
        "uniqueId",
        "sendData",
        "receiveData",
        "flitCreationTime",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int FlitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "address")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "addressLength")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+2;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopes")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "type_packet")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceId")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationId")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+8;
    if (fieldName[0]=='u' && strcmp(fieldName, "uniqueId")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendData")==0) return base+10;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiveData")==0) return base+11;
    if (fieldName[0]=='f' && strcmp(fieldName, "flitCreationTime")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FlitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **FlitDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FlitDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FlitDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Flit *pp = (Flit *)object; (void)pp;
    switch (field) {
        case 0: return 10;
        case 2: return 1024;
        case 10: return 7;
        case 11: return 7;
        default: return 0;
    }
}

const char *FlitDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flit *pp = (Flit *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlitDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flit *pp = (Flit *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getAddress(i));
        case 1: return long2string(pp->getAddressLength());
        case 2: return long2string(pp->getData(i));
        case 3: return long2string(pp->getHopes());
        case 4: return long2string(pp->getType());
        case 5: return long2string(pp->getType_packet());
        case 6: return long2string(pp->getSourceId());
        case 7: return long2string(pp->getDestinationId());
        case 8: return long2string(pp->getSize());
        case 9: return long2string(pp->getUniqueId());
        case 10: return long2string(pp->getSendData(i));
        case 11: return long2string(pp->getReceiveData(i));
        case 12: return simtime2string(pp->getFlitCreationTime());
        default: return "";
    }
}

bool FlitDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Flit *pp = (Flit *)object; (void)pp;
    switch (field) {
        case 0: pp->setAddress(i,string2long(value)); return true;
        case 1: pp->setAddressLength(string2long(value)); return true;
        case 2: pp->setData(i,string2long(value)); return true;
        case 3: pp->setHopes(string2long(value)); return true;
        case 4: pp->setType(string2long(value)); return true;
        case 5: pp->setType_packet(string2long(value)); return true;
        case 6: pp->setSourceId(string2long(value)); return true;
        case 7: pp->setDestinationId(string2long(value)); return true;
        case 8: pp->setSize(string2long(value)); return true;
        case 9: pp->setUniqueId(string2long(value)); return true;
        case 10: pp->setSendData(i,string2long(value)); return true;
        case 11: pp->setReceiveData(i,string2long(value)); return true;
        case 12: pp->setFlitCreationTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *FlitDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FlitDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Flit *pp = (Flit *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


