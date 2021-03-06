//
// Generated file, do not edit! Created by nedtool 5.4 from node/Flit.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __FLIT_M_H
#define __FLIT_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>node/Flit.msg:16</tt> by nedtool.
 * <pre>
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * packet Flit
 * {
 *     int address[10];
 *     int addressLength;
 *     int data[1024];
 *     int hopes;
 *     int type;
 *     int type_packet;
 *     int sourceId;
 *     int destinationId;
 *     int size;
 *     int uniqueId;
 *     int sendData[7];
 *     int receiveData[7];
 *     simtime_t flitCreationTime;
 * }
 * </pre>
 */
class Flit : public ::omnetpp::cPacket
{
  protected:
    int address[10];
    int addressLength;
    int data[1024];
    int hopes;
    int type;
    int type_packet;
    int sourceId;
    int destinationId;
    int size;
    int uniqueId;
    int sendData[7];
    int receiveData[7];
    ::omnetpp::simtime_t flitCreationTime;

  private:
    void copy(const Flit& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Flit&);

  public:
    Flit(const char *name=nullptr, short kind=0);
    Flit(const Flit& other);
    virtual ~Flit();
    Flit& operator=(const Flit& other);
    virtual Flit *dup() const override {return new Flit(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getAddressArraySize() const;
    virtual int getAddress(unsigned int k) const;
    virtual void setAddress(unsigned int k, int address);
    virtual int getAddressLength() const;
    virtual void setAddressLength(int addressLength);
    virtual unsigned int getDataArraySize() const;
    virtual int getData(unsigned int k) const;
    virtual void setData(unsigned int k, int data);
    virtual int getHopes() const;
    virtual void setHopes(int hopes);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getType_packet() const;
    virtual void setType_packet(int type_packet);
    virtual int getSourceId() const;
    virtual void setSourceId(int sourceId);
    virtual int getDestinationId() const;
    virtual void setDestinationId(int destinationId);
    virtual int getSize() const;
    virtual void setSize(int size);
    virtual int getUniqueId() const;
    virtual void setUniqueId(int uniqueId);
    virtual unsigned int getSendDataArraySize() const;
    virtual int getSendData(unsigned int k) const;
    virtual void setSendData(unsigned int k, int sendData);
    virtual unsigned int getReceiveDataArraySize() const;
    virtual int getReceiveData(unsigned int k) const;
    virtual void setReceiveData(unsigned int k, int receiveData);
    virtual ::omnetpp::simtime_t getFlitCreationTime() const;
    virtual void setFlitCreationTime(::omnetpp::simtime_t flitCreationTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Flit& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Flit& obj) {obj.parsimUnpack(b);}


#endif // ifndef __FLIT_M_H

