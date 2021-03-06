/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MIAScriptAPI_H
#define MIAScriptAPI_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "mia_types.h"

namespace scriptapi {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class MIAScriptAPIIf {
 public:
  virtual ~MIAScriptAPIIf() {}
  virtual void MIGetTaskParam(std::string& _return, const std::string& ParamName) = 0;
  virtual void MISetTaskParam(const std::string& ParamName, const std::string& ParamValue) = 0;
  virtual void MILogMsg(const std::string& Message) = 0;
};

class MIAScriptAPIIfFactory {
 public:
  typedef MIAScriptAPIIf Handler;

  virtual ~MIAScriptAPIIfFactory() {}

  virtual MIAScriptAPIIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MIAScriptAPIIf* /* handler */) = 0;
};

class MIAScriptAPIIfSingletonFactory : virtual public MIAScriptAPIIfFactory {
 public:
  MIAScriptAPIIfSingletonFactory(const boost::shared_ptr<MIAScriptAPIIf>& iface) : iface_(iface) {}
  virtual ~MIAScriptAPIIfSingletonFactory() {}

  virtual MIAScriptAPIIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MIAScriptAPIIf* /* handler */) {}

 protected:
  boost::shared_ptr<MIAScriptAPIIf> iface_;
};

class MIAScriptAPINull : virtual public MIAScriptAPIIf {
 public:
  virtual ~MIAScriptAPINull() {}
  void MIGetTaskParam(std::string& /* _return */, const std::string& /* ParamName */) {
    return;
  }
  void MISetTaskParam(const std::string& /* ParamName */, const std::string& /* ParamValue */) {
    return;
  }
  void MILogMsg(const std::string& /* Message */) {
    return;
  }
};

typedef struct _MIAScriptAPI_MIGetTaskParam_args__isset {
  _MIAScriptAPI_MIGetTaskParam_args__isset() : ParamName(false) {}
  bool ParamName :1;
} _MIAScriptAPI_MIGetTaskParam_args__isset;

class MIAScriptAPI_MIGetTaskParam_args {
 public:

  MIAScriptAPI_MIGetTaskParam_args(const MIAScriptAPI_MIGetTaskParam_args&);
  MIAScriptAPI_MIGetTaskParam_args& operator=(const MIAScriptAPI_MIGetTaskParam_args&);
  MIAScriptAPI_MIGetTaskParam_args() : ParamName() {
  }

  virtual ~MIAScriptAPI_MIGetTaskParam_args() throw();
  std::string ParamName;

  _MIAScriptAPI_MIGetTaskParam_args__isset __isset;

  void __set_ParamName(const std::string& val);

  bool operator == (const MIAScriptAPI_MIGetTaskParam_args & rhs) const
  {
    if (!(ParamName == rhs.ParamName))
      return false;
    return true;
  }
  bool operator != (const MIAScriptAPI_MIGetTaskParam_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MIGetTaskParam_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MIGetTaskParam_pargs {
 public:


  virtual ~MIAScriptAPI_MIGetTaskParam_pargs() throw();
  const std::string* ParamName;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MIAScriptAPI_MIGetTaskParam_result__isset {
  _MIAScriptAPI_MIGetTaskParam_result__isset() : success(false) {}
  bool success :1;
} _MIAScriptAPI_MIGetTaskParam_result__isset;

class MIAScriptAPI_MIGetTaskParam_result {
 public:

  MIAScriptAPI_MIGetTaskParam_result(const MIAScriptAPI_MIGetTaskParam_result&);
  MIAScriptAPI_MIGetTaskParam_result& operator=(const MIAScriptAPI_MIGetTaskParam_result&);
  MIAScriptAPI_MIGetTaskParam_result() : success() {
  }

  virtual ~MIAScriptAPI_MIGetTaskParam_result() throw();
  std::string success;

  _MIAScriptAPI_MIGetTaskParam_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const MIAScriptAPI_MIGetTaskParam_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const MIAScriptAPI_MIGetTaskParam_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MIGetTaskParam_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MIAScriptAPI_MIGetTaskParam_presult__isset {
  _MIAScriptAPI_MIGetTaskParam_presult__isset() : success(false) {}
  bool success :1;
} _MIAScriptAPI_MIGetTaskParam_presult__isset;

class MIAScriptAPI_MIGetTaskParam_presult {
 public:


  virtual ~MIAScriptAPI_MIGetTaskParam_presult() throw();
  std::string* success;

  _MIAScriptAPI_MIGetTaskParam_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _MIAScriptAPI_MISetTaskParam_args__isset {
  _MIAScriptAPI_MISetTaskParam_args__isset() : ParamName(false), ParamValue(false) {}
  bool ParamName :1;
  bool ParamValue :1;
} _MIAScriptAPI_MISetTaskParam_args__isset;

class MIAScriptAPI_MISetTaskParam_args {
 public:

  MIAScriptAPI_MISetTaskParam_args(const MIAScriptAPI_MISetTaskParam_args&);
  MIAScriptAPI_MISetTaskParam_args& operator=(const MIAScriptAPI_MISetTaskParam_args&);
  MIAScriptAPI_MISetTaskParam_args() : ParamName(), ParamValue() {
  }

  virtual ~MIAScriptAPI_MISetTaskParam_args() throw();
  std::string ParamName;
  std::string ParamValue;

  _MIAScriptAPI_MISetTaskParam_args__isset __isset;

  void __set_ParamName(const std::string& val);

  void __set_ParamValue(const std::string& val);

  bool operator == (const MIAScriptAPI_MISetTaskParam_args & rhs) const
  {
    if (!(ParamName == rhs.ParamName))
      return false;
    if (!(ParamValue == rhs.ParamValue))
      return false;
    return true;
  }
  bool operator != (const MIAScriptAPI_MISetTaskParam_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MISetTaskParam_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MISetTaskParam_pargs {
 public:


  virtual ~MIAScriptAPI_MISetTaskParam_pargs() throw();
  const std::string* ParamName;
  const std::string* ParamValue;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MISetTaskParam_result {
 public:

  MIAScriptAPI_MISetTaskParam_result(const MIAScriptAPI_MISetTaskParam_result&);
  MIAScriptAPI_MISetTaskParam_result& operator=(const MIAScriptAPI_MISetTaskParam_result&);
  MIAScriptAPI_MISetTaskParam_result() {
  }

  virtual ~MIAScriptAPI_MISetTaskParam_result() throw();

  bool operator == (const MIAScriptAPI_MISetTaskParam_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MIAScriptAPI_MISetTaskParam_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MISetTaskParam_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MISetTaskParam_presult {
 public:


  virtual ~MIAScriptAPI_MISetTaskParam_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _MIAScriptAPI_MILogMsg_args__isset {
  _MIAScriptAPI_MILogMsg_args__isset() : Message(false) {}
  bool Message :1;
} _MIAScriptAPI_MILogMsg_args__isset;

class MIAScriptAPI_MILogMsg_args {
 public:

  MIAScriptAPI_MILogMsg_args(const MIAScriptAPI_MILogMsg_args&);
  MIAScriptAPI_MILogMsg_args& operator=(const MIAScriptAPI_MILogMsg_args&);
  MIAScriptAPI_MILogMsg_args() : Message() {
  }

  virtual ~MIAScriptAPI_MILogMsg_args() throw();
  std::string Message;

  _MIAScriptAPI_MILogMsg_args__isset __isset;

  void __set_Message(const std::string& val);

  bool operator == (const MIAScriptAPI_MILogMsg_args & rhs) const
  {
    if (!(Message == rhs.Message))
      return false;
    return true;
  }
  bool operator != (const MIAScriptAPI_MILogMsg_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MILogMsg_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MILogMsg_pargs {
 public:


  virtual ~MIAScriptAPI_MILogMsg_pargs() throw();
  const std::string* Message;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MILogMsg_result {
 public:

  MIAScriptAPI_MILogMsg_result(const MIAScriptAPI_MILogMsg_result&);
  MIAScriptAPI_MILogMsg_result& operator=(const MIAScriptAPI_MILogMsg_result&);
  MIAScriptAPI_MILogMsg_result() {
  }

  virtual ~MIAScriptAPI_MILogMsg_result() throw();

  bool operator == (const MIAScriptAPI_MILogMsg_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MIAScriptAPI_MILogMsg_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MIAScriptAPI_MILogMsg_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MIAScriptAPI_MILogMsg_presult {
 public:


  virtual ~MIAScriptAPI_MILogMsg_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class MIAScriptAPIClient : virtual public MIAScriptAPIIf {
 public:
  MIAScriptAPIClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MIAScriptAPIClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void MIGetTaskParam(std::string& _return, const std::string& ParamName);
  void send_MIGetTaskParam(const std::string& ParamName);
  void recv_MIGetTaskParam(std::string& _return);
  void MISetTaskParam(const std::string& ParamName, const std::string& ParamValue);
  void send_MISetTaskParam(const std::string& ParamName, const std::string& ParamValue);
  void recv_MISetTaskParam();
  void MILogMsg(const std::string& Message);
  void send_MILogMsg(const std::string& Message);
  void recv_MILogMsg();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MIAScriptAPIProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<MIAScriptAPIIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (MIAScriptAPIProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_MIGetTaskParam(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_MISetTaskParam(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_MILogMsg(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MIAScriptAPIProcessor(boost::shared_ptr<MIAScriptAPIIf> iface) :
    iface_(iface) {
    processMap_["MIGetTaskParam"] = &MIAScriptAPIProcessor::process_MIGetTaskParam;
    processMap_["MISetTaskParam"] = &MIAScriptAPIProcessor::process_MISetTaskParam;
    processMap_["MILogMsg"] = &MIAScriptAPIProcessor::process_MILogMsg;
  }

  virtual ~MIAScriptAPIProcessor() {}
};

class MIAScriptAPIProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MIAScriptAPIProcessorFactory(const ::boost::shared_ptr< MIAScriptAPIIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< MIAScriptAPIIfFactory > handlerFactory_;
};

class MIAScriptAPIMultiface : virtual public MIAScriptAPIIf {
 public:
  MIAScriptAPIMultiface(std::vector<boost::shared_ptr<MIAScriptAPIIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MIAScriptAPIMultiface() {}
 protected:
  std::vector<boost::shared_ptr<MIAScriptAPIIf> > ifaces_;
  MIAScriptAPIMultiface() {}
  void add(boost::shared_ptr<MIAScriptAPIIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void MIGetTaskParam(std::string& _return, const std::string& ParamName) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->MIGetTaskParam(_return, ParamName);
    }
    ifaces_[i]->MIGetTaskParam(_return, ParamName);
    return;
  }

  void MISetTaskParam(const std::string& ParamName, const std::string& ParamValue) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->MISetTaskParam(ParamName, ParamValue);
    }
    ifaces_[i]->MISetTaskParam(ParamName, ParamValue);
  }

  void MILogMsg(const std::string& Message) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->MILogMsg(Message);
    }
    ifaces_[i]->MILogMsg(Message);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class MIAScriptAPIConcurrentClient : virtual public MIAScriptAPIIf {
 public:
  MIAScriptAPIConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MIAScriptAPIConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void MIGetTaskParam(std::string& _return, const std::string& ParamName);
  int32_t send_MIGetTaskParam(const std::string& ParamName);
  void recv_MIGetTaskParam(std::string& _return, const int32_t seqid);
  void MISetTaskParam(const std::string& ParamName, const std::string& ParamValue);
  int32_t send_MISetTaskParam(const std::string& ParamName, const std::string& ParamValue);
  void recv_MISetTaskParam(const int32_t seqid);
  void MILogMsg(const std::string& Message);
  int32_t send_MILogMsg(const std::string& Message);
  void recv_MILogMsg(const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
