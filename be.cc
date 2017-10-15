#include "gen-cpp/MIAScriptAPI.h"

#include <chrono>
#include <mutex>
#include <thread>

#include <boost/format.hpp>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>
#include <map>

//#include <gflags/gflags.h>

//DEFINE_int32(port, 9090, "Port to use."); 
int FLAGS_port = 9090;

uint64_t js_date_now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace scriptapi;

typedef std::map<std::string, std::string> TypParamMap;

class Service : virtual public MIAScriptAPIIf {
private:
   TypParamMap m_mapParams;
 public:
  Service() : start_time_ms_(js_date_now()) {
     // Pretend that the user has configured this task parameter.
     MISetTaskParam("shortUrl", "http://goo.gl/P79A");
  }

  virtual void MIGetTaskParam(std::string& _return, const std::string& ParamName) {
     _return = "";
     TypParamMap::iterator iter = m_mapParams.find(ParamName);
     if(m_mapParams.end() != iter) {
        _return = iter->second;
     }
     std::cout << "MIGetTaskParam called with " << ParamName << " is returning " << _return << std::endl;
  }
  virtual void MISetTaskParam(const std::string& ParamName, const std::string& ParamValue) {
     std::cout << "MISetTaskParam called with " << ParamName << "=" << ParamValue << std::endl;
     m_mapParams[ParamName] = ParamValue;
  }
  virtual void MILogMsg(const std::string& Message) {
     time_t mytime;
     time(&mytime);
     struct tm *mytm = localtime(&mytime);
     char szTmpTimeStamp[64];
     strftime(szTmpTimeStamp, sizeof(szTmpTimeStamp), "%Y-%m-%d %H:%M:%S ", mytm);
     std::cout << szTmpTimeStamp << Message << std::endl;
  }

  //void api_post_message(const MessageToPost& message) {
  //  std::cout << message.user << ": " << message.message << " (" << js_date_now() - message.ms << "ms)." << std::endl;
  //  {
  //    std::lock_guard<std::mutex> lock(mutex_);
  //    messages_.push_back(std::tie(message.user, message.message, message.ms));
  //  }
  //}
  //void api_status(APIStatus& status) {
  //  status.status = boost::str(boost::format("Live, uptime %.0lf seconds.") % (0.001 * (js_date_now() - start_time_ms_)));
  //}
  //void api_messages_log(Log& log) {
  //  const uint64_t now = js_date_now();
  //  std::lock_guard<std::mutex> lock(mutex_);
  //  log.total = messages_.size();
  //  log.messages.resize(messages_.size());
  //  for (size_t i = 0; i < messages_.size(); ++i) {
  //    const auto& m = messages_[i];
  //    log.messages[i] = boost::str(boost::format("%s: %s (%.0lf seconds ago).") % std::get<0>(m) % std::get<1>(m) % (0.001 * (now - std::get<2>(m))));
  //  }
  //}
  //void api_recent_messages_log(Log& recent_log, const RecentMessagesLogParams& params) {
  //  const uint64_t now = js_date_now();
  //  std::lock_guard<std::mutex> lock(mutex_);
  //  recent_log.messages.clear();
  //  const uint64_t cutoff_ms = static_cast<int64_t>(now - 1000.0 * params.seconds); 
  //  for (size_t i = 0; i < messages_.size(); ++i) {
  //    const auto& m = messages_[i];
  //    if (std::get<2>(m) >= cutoff_ms) {
  //      recent_log.messages.push_back(boost::str(boost::format("%s: %s (%.0lf seconds ago).") % std::get<0>(m) % std::get<1>(m) % (0.001 * (now - std::get<2>(m)))));
  //    }
  //  }
  //  recent_log.total = recent_log.messages.size();
  //}
  //void api_add(AddResult& result, const api::AddArguments& arguments) {
  //  result.sum = arguments.left_hand_side + arguments.right_hand_side;
  //}

 private:
  std::mutex mutex_;
  uint64_t start_time_ms_;
  std::vector<std::tuple<std::string, std::string, uint64_t> > messages_;
};

int main(int argc, char** argv) {
  //if (!google::ParseCommandLineFlags(&argc, &argv, true)) {
  //  return -1;
  //}
  boost::shared_ptr<Service> handler(new Service());
  boost::shared_ptr<TProcessor> processor(new MIAScriptAPIProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(FLAGS_port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  std::cout << "About to start server on port " <<  FLAGS_port << std::endl;
  TSimpleServer(processor, serverTransport, transportFactory, protocolFactory).serve();
}
