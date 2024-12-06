//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/DemoSafetyMessage.msg.
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
#include <memory>
#include "DemoSafetyMessage_m.h"

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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

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

Register_Class(DemoSafetyMessage)

DemoSafetyMessage::DemoSafetyMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

DemoSafetyMessage::DemoSafetyMessage(const DemoSafetyMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

DemoSafetyMessage::~DemoSafetyMessage()
{
}

DemoSafetyMessage& DemoSafetyMessage::operator=(const DemoSafetyMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void DemoSafetyMessage::copy(const DemoSafetyMessage& other)
{
    this->senderAddress = other.senderAddress;
    this->senderPos = other.senderPos;
    this->psid = other.psid;
    this->channelNumber = other.channelNumber;
    this->senderId = other.senderId;
    this->senderSpeed = other.senderSpeed;
}

void DemoSafetyMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->psid);
    doParsimPacking(b,this->channelNumber);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->senderSpeed);
}

void DemoSafetyMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->psid);
    doParsimUnpacking(b,this->channelNumber);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->senderSpeed);
}

int DemoSafetyMessage::getSenderAddress() const
{
    return this->senderAddress;
}

void DemoSafetyMessage::setSenderAddress(int senderAddress)
{
    this->senderAddress = senderAddress;
}

const Coord& DemoSafetyMessage::getSenderPos() const
{
    return this->senderPos;
}

void DemoSafetyMessage::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

int DemoSafetyMessage::getPsid() const
{
    return this->psid;
}

void DemoSafetyMessage::setPsid(int psid)
{
    this->psid = psid;
}

int DemoSafetyMessage::getChannelNumber() const
{
    return this->channelNumber;
}

void DemoSafetyMessage::setChannelNumber(int channelNumber)
{
    this->channelNumber = channelNumber;
}

const char * DemoSafetyMessage::getSenderId() const
{
    return this->senderId.c_str();
}

void DemoSafetyMessage::setSenderId(const char * senderId)
{
    this->senderId = senderId;
}

const Coord& DemoSafetyMessage::getSenderSpeed() const
{
    return this->senderSpeed;
}

void DemoSafetyMessage::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

class DemoSafetyMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_senderAddress,
        FIELD_senderPos,
        FIELD_psid,
        FIELD_channelNumber,
        FIELD_senderId,
        FIELD_senderSpeed,
    };
  public:
    DemoSafetyMessageDescriptor();
    virtual ~DemoSafetyMessageDescriptor();

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

Register_ClassDescriptor(DemoSafetyMessageDescriptor)

DemoSafetyMessageDescriptor::DemoSafetyMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::DemoSafetyMessage)), "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

DemoSafetyMessageDescriptor::~DemoSafetyMessageDescriptor()
{
    delete[] propertynames;
}

bool DemoSafetyMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DemoSafetyMessage *>(obj)!=nullptr;
}

const char **DemoSafetyMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DemoSafetyMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DemoSafetyMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int DemoSafetyMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderAddress
        0,    // FIELD_senderPos
        FD_ISEDITABLE,    // FIELD_psid
        FD_ISEDITABLE,    // FIELD_channelNumber
        FD_ISEDITABLE,    // FIELD_senderId
        0,    // FIELD_senderSpeed
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *DemoSafetyMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderAddress",
        "senderPos",
        "psid",
        "channelNumber",
        "senderId",
        "senderSpeed",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int DemoSafetyMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderAddress") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderPos") == 0) return base+1;
    if (fieldName[0] == 'p' && strcmp(fieldName, "psid") == 0) return base+2;
    if (fieldName[0] == 'c' && strcmp(fieldName, "channelNumber") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderId") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderSpeed") == 0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DemoSafetyMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_senderAddress
        "veins::Coord",    // FIELD_senderPos
        "int",    // FIELD_psid
        "int",    // FIELD_channelNumber
        "string",    // FIELD_senderId
        "veins::Coord",    // FIELD_senderSpeed
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **DemoSafetyMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *DemoSafetyMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int DemoSafetyMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DemoSafetyMessage *pp = (DemoSafetyMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *DemoSafetyMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DemoSafetyMessage *pp = (DemoSafetyMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DemoSafetyMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DemoSafetyMessage *pp = (DemoSafetyMessage *)object; (void)pp;
    switch (field) {
        case FIELD_senderAddress: return long2string(pp->getSenderAddress());
        case FIELD_senderPos: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case FIELD_psid: return long2string(pp->getPsid());
        case FIELD_channelNumber: return long2string(pp->getChannelNumber());
        case FIELD_senderId: return oppstring2string(pp->getSenderId());
        case FIELD_senderSpeed: {std::stringstream out; out << pp->getSenderSpeed(); return out.str();}
        default: return "";
    }
}

bool DemoSafetyMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DemoSafetyMessage *pp = (DemoSafetyMessage *)object; (void)pp;
    switch (field) {
        case FIELD_senderAddress: pp->setSenderAddress(string2long(value)); return true;
        case FIELD_psid: pp->setPsid(string2long(value)); return true;
        case FIELD_channelNumber: pp->setChannelNumber(string2long(value)); return true;
        case FIELD_senderId: pp->setSenderId((value)); return true;
        default: return false;
    }
}

const char *DemoSafetyMessageDescriptor::getFieldStructName(int field) const
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

void *DemoSafetyMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DemoSafetyMessage *pp = (DemoSafetyMessage *)object; (void)pp;
    switch (field) {
        case FIELD_senderPos: return toVoidPtr(&pp->getSenderPos()); break;
        case FIELD_senderSpeed: return toVoidPtr(&pp->getSenderSpeed()); break;
        default: return nullptr;
    }
}

Register_Class(EmergencyVehicleMessage)

EmergencyVehicleMessage::EmergencyVehicleMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

EmergencyVehicleMessage::EmergencyVehicleMessage(const EmergencyVehicleMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

EmergencyVehicleMessage::~EmergencyVehicleMessage()
{
}

EmergencyVehicleMessage& EmergencyVehicleMessage::operator=(const EmergencyVehicleMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void EmergencyVehicleMessage::copy(const EmergencyVehicleMessage& other)
{
    this->vehicleId = other.vehicleId;
    this->latitude = other.latitude;
    this->longitude = other.longitude;
    this->speed = other.speed;
    this->direction = other.direction;
    this->timestamp = other.timestamp;
}

void EmergencyVehicleMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->latitude);
    doParsimPacking(b,this->longitude);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->direction);
    doParsimPacking(b,this->timestamp);
}

void EmergencyVehicleMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->latitude);
    doParsimUnpacking(b,this->longitude);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->direction);
    doParsimUnpacking(b,this->timestamp);
}

const char * EmergencyVehicleMessage::getVehicleId() const
{
    return this->vehicleId.c_str();
}

void EmergencyVehicleMessage::setVehicleId(const char * vehicleId)
{
    this->vehicleId = vehicleId;
}

double EmergencyVehicleMessage::getLatitude() const
{
    return this->latitude;
}

void EmergencyVehicleMessage::setLatitude(double latitude)
{
    this->latitude = latitude;
}

double EmergencyVehicleMessage::getLongitude() const
{
    return this->longitude;
}

void EmergencyVehicleMessage::setLongitude(double longitude)
{
    this->longitude = longitude;
}

double EmergencyVehicleMessage::getSpeed() const
{
    return this->speed;
}

void EmergencyVehicleMessage::setSpeed(double speed)
{
    this->speed = speed;
}

const char * EmergencyVehicleMessage::getDirection() const
{
    return this->direction.c_str();
}

void EmergencyVehicleMessage::setDirection(const char * direction)
{
    this->direction = direction;
}

double EmergencyVehicleMessage::getTimestamp() const
{
    return this->timestamp;
}

void EmergencyVehicleMessage::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class EmergencyVehicleMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_vehicleId,
        FIELD_latitude,
        FIELD_longitude,
        FIELD_speed,
        FIELD_direction,
        FIELD_timestamp,
    };
  public:
    EmergencyVehicleMessageDescriptor();
    virtual ~EmergencyVehicleMessageDescriptor();

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

Register_ClassDescriptor(EmergencyVehicleMessageDescriptor)

EmergencyVehicleMessageDescriptor::EmergencyVehicleMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::EmergencyVehicleMessage)), "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

EmergencyVehicleMessageDescriptor::~EmergencyVehicleMessageDescriptor()
{
    delete[] propertynames;
}

bool EmergencyVehicleMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EmergencyVehicleMessage *>(obj)!=nullptr;
}

const char **EmergencyVehicleMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EmergencyVehicleMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EmergencyVehicleMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int EmergencyVehicleMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleId
        FD_ISEDITABLE,    // FIELD_latitude
        FD_ISEDITABLE,    // FIELD_longitude
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_direction
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *EmergencyVehicleMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "latitude",
        "longitude",
        "speed",
        "direction",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int EmergencyVehicleMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'v' && strcmp(fieldName, "vehicleId") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "latitude") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "longitude") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "speed") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "direction") == 0) return base+4;
    if (fieldName[0] == 't' && strcmp(fieldName, "timestamp") == 0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EmergencyVehicleMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_vehicleId
        "double",    // FIELD_latitude
        "double",    // FIELD_longitude
        "double",    // FIELD_speed
        "string",    // FIELD_direction
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **EmergencyVehicleMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *EmergencyVehicleMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int EmergencyVehicleMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EmergencyVehicleMessage *pp = (EmergencyVehicleMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EmergencyVehicleMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmergencyVehicleMessage *pp = (EmergencyVehicleMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EmergencyVehicleMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmergencyVehicleMessage *pp = (EmergencyVehicleMessage *)object; (void)pp;
    switch (field) {
        case FIELD_vehicleId: return oppstring2string(pp->getVehicleId());
        case FIELD_latitude: return double2string(pp->getLatitude());
        case FIELD_longitude: return double2string(pp->getLongitude());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_direction: return oppstring2string(pp->getDirection());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

bool EmergencyVehicleMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EmergencyVehicleMessage *pp = (EmergencyVehicleMessage *)object; (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId((value)); return true;
        case FIELD_latitude: pp->setLatitude(string2double(value)); return true;
        case FIELD_longitude: pp->setLongitude(string2double(value)); return true;
        case FIELD_speed: pp->setSpeed(string2double(value)); return true;
        case FIELD_direction: pp->setDirection((value)); return true;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); return true;
        default: return false;
    }
}

const char *EmergencyVehicleMessageDescriptor::getFieldStructName(int field) const
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

void *EmergencyVehicleMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EmergencyVehicleMessage *pp = (EmergencyVehicleMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(TrafficLightChangeMeessage)

TrafficLightChangeMeessage::TrafficLightChangeMeessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

TrafficLightChangeMeessage::TrafficLightChangeMeessage(const TrafficLightChangeMeessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

TrafficLightChangeMeessage::~TrafficLightChangeMeessage()
{
}

TrafficLightChangeMeessage& TrafficLightChangeMeessage::operator=(const TrafficLightChangeMeessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void TrafficLightChangeMeessage::copy(const TrafficLightChangeMeessage& other)
{
    this->ambulanceId = other.ambulanceId;
    this->latitude = other.latitude;
    this->longitude = other.longitude;
    this->edge = other.edge;
    this->lane = other.lane;
    this->speed = other.speed;
    this->timestamp = other.timestamp;
    this->greenPhaseIndex = other.greenPhaseIndex;
}

void TrafficLightChangeMeessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->ambulanceId);
    doParsimPacking(b,this->latitude);
    doParsimPacking(b,this->longitude);
    doParsimPacking(b,this->edge);
    doParsimPacking(b,this->lane);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->greenPhaseIndex);
}

void TrafficLightChangeMeessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->ambulanceId);
    doParsimUnpacking(b,this->latitude);
    doParsimUnpacking(b,this->longitude);
    doParsimUnpacking(b,this->edge);
    doParsimUnpacking(b,this->lane);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->greenPhaseIndex);
}

const char * TrafficLightChangeMeessage::getAmbulanceId() const
{
    return this->ambulanceId.c_str();
}

void TrafficLightChangeMeessage::setAmbulanceId(const char * ambulanceId)
{
    this->ambulanceId = ambulanceId;
}

double TrafficLightChangeMeessage::getLatitude() const
{
    return this->latitude;
}

void TrafficLightChangeMeessage::setLatitude(double latitude)
{
    this->latitude = latitude;
}

double TrafficLightChangeMeessage::getLongitude() const
{
    return this->longitude;
}

void TrafficLightChangeMeessage::setLongitude(double longitude)
{
    this->longitude = longitude;
}

const char * TrafficLightChangeMeessage::getEdge() const
{
    return this->edge.c_str();
}

void TrafficLightChangeMeessage::setEdge(const char * edge)
{
    this->edge = edge;
}

const char * TrafficLightChangeMeessage::getLane() const
{
    return this->lane.c_str();
}

void TrafficLightChangeMeessage::setLane(const char * lane)
{
    this->lane = lane;
}

double TrafficLightChangeMeessage::getSpeed() const
{
    return this->speed;
}

void TrafficLightChangeMeessage::setSpeed(double speed)
{
    this->speed = speed;
}

double TrafficLightChangeMeessage::getTimestamp() const
{
    return this->timestamp;
}

void TrafficLightChangeMeessage::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

int TrafficLightChangeMeessage::getGreenPhaseIndex() const
{
    return this->greenPhaseIndex;
}

void TrafficLightChangeMeessage::setGreenPhaseIndex(int greenPhaseIndex)
{
    this->greenPhaseIndex = greenPhaseIndex;
}

class TrafficLightChangeMeessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_ambulanceId,
        FIELD_latitude,
        FIELD_longitude,
        FIELD_edge,
        FIELD_lane,
        FIELD_speed,
        FIELD_timestamp,
        FIELD_greenPhaseIndex,
    };
  public:
    TrafficLightChangeMeessageDescriptor();
    virtual ~TrafficLightChangeMeessageDescriptor();

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

Register_ClassDescriptor(TrafficLightChangeMeessageDescriptor)

TrafficLightChangeMeessageDescriptor::TrafficLightChangeMeessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::TrafficLightChangeMeessage)), "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

TrafficLightChangeMeessageDescriptor::~TrafficLightChangeMeessageDescriptor()
{
    delete[] propertynames;
}

bool TrafficLightChangeMeessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TrafficLightChangeMeessage *>(obj)!=nullptr;
}

const char **TrafficLightChangeMeessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TrafficLightChangeMeessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TrafficLightChangeMeessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int TrafficLightChangeMeessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ambulanceId
        FD_ISEDITABLE,    // FIELD_latitude
        FD_ISEDITABLE,    // FIELD_longitude
        FD_ISEDITABLE,    // FIELD_edge
        FD_ISEDITABLE,    // FIELD_lane
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_greenPhaseIndex
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *TrafficLightChangeMeessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ambulanceId",
        "latitude",
        "longitude",
        "edge",
        "lane",
        "speed",
        "timestamp",
        "greenPhaseIndex",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int TrafficLightChangeMeessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "ambulanceId") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "latitude") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "longitude") == 0) return base+2;
    if (fieldName[0] == 'e' && strcmp(fieldName, "edge") == 0) return base+3;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lane") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "speed") == 0) return base+5;
    if (fieldName[0] == 't' && strcmp(fieldName, "timestamp") == 0) return base+6;
    if (fieldName[0] == 'g' && strcmp(fieldName, "greenPhaseIndex") == 0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TrafficLightChangeMeessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_ambulanceId
        "double",    // FIELD_latitude
        "double",    // FIELD_longitude
        "string",    // FIELD_edge
        "string",    // FIELD_lane
        "double",    // FIELD_speed
        "double",    // FIELD_timestamp
        "int",    // FIELD_greenPhaseIndex
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **TrafficLightChangeMeessageDescriptor::getFieldPropertyNames(int field) const
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

const char *TrafficLightChangeMeessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int TrafficLightChangeMeessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TrafficLightChangeMeessage *pp = (TrafficLightChangeMeessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TrafficLightChangeMeessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrafficLightChangeMeessage *pp = (TrafficLightChangeMeessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TrafficLightChangeMeessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TrafficLightChangeMeessage *pp = (TrafficLightChangeMeessage *)object; (void)pp;
    switch (field) {
        case FIELD_ambulanceId: return oppstring2string(pp->getAmbulanceId());
        case FIELD_latitude: return double2string(pp->getLatitude());
        case FIELD_longitude: return double2string(pp->getLongitude());
        case FIELD_edge: return oppstring2string(pp->getEdge());
        case FIELD_lane: return oppstring2string(pp->getLane());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_greenPhaseIndex: return long2string(pp->getGreenPhaseIndex());
        default: return "";
    }
}

bool TrafficLightChangeMeessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TrafficLightChangeMeessage *pp = (TrafficLightChangeMeessage *)object; (void)pp;
    switch (field) {
        case FIELD_ambulanceId: pp->setAmbulanceId((value)); return true;
        case FIELD_latitude: pp->setLatitude(string2double(value)); return true;
        case FIELD_longitude: pp->setLongitude(string2double(value)); return true;
        case FIELD_edge: pp->setEdge((value)); return true;
        case FIELD_lane: pp->setLane((value)); return true;
        case FIELD_speed: pp->setSpeed(string2double(value)); return true;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); return true;
        case FIELD_greenPhaseIndex: pp->setGreenPhaseIndex(string2long(value)); return true;
        default: return false;
    }
}

const char *TrafficLightChangeMeessageDescriptor::getFieldStructName(int field) const
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

void *TrafficLightChangeMeessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TrafficLightChangeMeessage *pp = (TrafficLightChangeMeessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace veins

