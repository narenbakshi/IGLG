#pragma once

#ifdef __cplusplus
  #define EXPORT_C extern "C"
#else
  #define EXPORT_C
#endif

#ifdef __cplusplus  // Enabled only for C++ compilers
#include <cstring> // memcpy
#include <cstdlib> //realloc

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <memory>
#include <string>

#include <vsomeip/vsomeip.hpp>
#include "../../factory/handlerFactory.h"



#include "/home/job2/Thesis/responses.h"
#include "/home/job2/Thesis/analyze.h"


/**
 * @brief Function to initialze nanomsg pub sub.
 * @param structframwork Sturcture of nanomsg fucntion pointers.
 * @return void: Returns nothing.
 */



/**************************************subscribe**********************/
class subVsomeIP {
 public:
  enum SubscriptionReturnCode : std::uint8_t { ACCPETED = 0x00, REJECTED = 0x07 };

  subVsomeIP(std ::string topic){
    appl_ = (vsomeip::runtime::get()->create_application("client-sample"));
    if (topic.compare("Tracer") == 0){
        service_id_ = 0x1234, instance_id_ = 0x5678;
      eventgroup_id_ = 0x4455, event_id_ = 0x8777;
      ready_method_id_ = 0x7777;
      }
      else{
        service_id_ = 0x0248, instance_id_ = 0x5422;
      eventgroup_id_ = 0x4455, event_id_ = 0x8777;
      ready_method_id_ = 0x1421;
        
      }
      if (topic.compare("Benchi") == 0){
        service_id_ = 0x1245, instance_id_ = 0x5645;
      eventgroup_id_ = 0x4445, event_id_ = 0x8745;
      ready_method_id_ = 0x7745;
      }
    
  } 

  ~subVsomeIP() { exit(); }

  bool init() {
    if (!appl_->init()) {
      std::cout << ">>>> error: ||| "
                << "Couldn't initialize application" << std::endl;
      return false;
    }

    appl_->register_state_handler([this](vsomeip::state_type_e e) { this->on_state(e); });

appl_->register_message_handler(
                service_id_, instance_id_, event_id_,
                std::bind(&subVsomeIP::on_message, this,
                        std::placeholders::_1));

    appl_->register_availability_handler(
        service_id_, instance_id_,
        [this](vsomeip::service_t service, vsomeip::instance_t instance, bool is_available) {
          this->on_availability(service, instance, is_available);
        });

    appl_->register_subscription_status_handler(
        service_id_, instance_id_, eventgroup_id_, event_id_,
        [this](const vsomeip::service_t service, const vsomeip::instance_t instance,
               const vsomeip::eventgroup_t eventgroup, const vsomeip::eventgroup_t event_id,
               const uint16_t sub_code) {
          this->on_subscription_status_change(service, instance, eventgroup, event_id, sub_code);
        });

    appl_->register_subscription_handler(
        service_id_, instance_id_, eventgroup_id_,
        [this](const vsomeip::client_t client, const vsomeip::uid_t uid, const vsomeip::gid_t gid,
               const bool stats) -> bool {
          return on_subscription_change(client, uid, gid, stats);
        });

    appl_->request_service(service_id_, instance_id_);

    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(eventgroup_id_);
    appl_->request_event(service_id_, instance_id_, event_id_, its_groups,
                                vsomeip::event_type_e::ET_EVENT);
    appl_->subscribe(service_id_, instance_id_, eventgroup_id_);

    return true;
  }

  void start() {
    someip_thread_ = std::thread([this]() { appl_->start(); });
    is_someip_running_ = true;
  }
  void on_message(const std::shared_ptr<vsomeip::message> &_response) {
        
        
        std::shared_ptr<vsomeip::payload> its_payload =
                _response->get_payload();
                auto newdata = its_payload.get();
        std::string resp = std::string(
                    reinterpret_cast<const char*>(its_payload->get_data()), 0,
                    its_payload->get_length());
        std::cout <<"receiving data " << resp.c_str() << std::endl; 
        char* payloadptr = const_cast<char*>(resp.c_str());
        void *context; char *topicName; int topicLen;
        if(service_id_ == 0x1234)
        {
            formattersubHandler->msgarrvd(context,topicName,topicLen,payloadptr);
        }
        else
        {
            analyzesubHandler->msgarrvd(context,topicName,topicLen,payloadptr);
        }
        
        }

  void run(const std::chrono::milliseconds &duration) {
    auto ready_thread = std::thread([this]() { inform_sender(); });
    //auto shutdown_thread = std::thread([this, duration]() { close_sender(duration); });

    while (!stop_token_) {  
      }
    
    ready_thread.join();
    //shutdown_thread.join();
  }

  bool exit() {
    stop_token_ = true;
    appl_->clear_all_handler();
    appl_->unsubscribe(service_id_, instance_id_, eventgroup_id_);
    appl_->release_event(service_id_, instance_id_, event_id_);
    appl_->release_service(service_id_, instance_id_);
    appl_->stop();
    if (someip_thread_.joinable()) {
      someip_thread_.join();
      is_someip_running_ = false;
    }
    return true;
  }

  void on_state(vsomeip::state_type_e e) {
    is_registered_ = e == vsomeip::state_type_e::ST_REGISTERED;
    std::cout << ">>>> info ||| "
              << (is_registered_ ? "service is registered" : "service is de-registered")
              << std::endl;
    cv_.notify_one();
  }


  void on_availability(vsomeip::service_t service, vsomeip::instance_t instance,
                       bool is_available) {
    is_available_ = service == service_id_ && instance_id_ == instance && is_available;
    std::cout << ">>>> info ||| "
              << "publisher service is " << (is_available_ ? "available" : "not availale")
              << std::endl;
  }

  void inform_sender() {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() { return is_subscribed_.load(); });
    std::cout << ">>>> info ||| "
              << "sending ack message to publisher" << std::endl;
    std::shared_ptr<vsomeip::message> ready_req = vsomeip::runtime::get()->create_request();
    ready_req->set_service(service_id_);
    ready_req->set_instance(instance_id_);
    ready_req->set_method(ready_method_id_);
    appl_->send(ready_req);

    start_clock_ = true;
    cv_.notify_one();
  }

  void close_sender(const std::chrono::milliseconds &duration) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() { return start_clock_.load(); });

    std::cout << ">>>> info ||| "
              << "starting the clock for end" << std::endl;

    std::this_thread::sleep_for(duration);

    std::cout << ">>>> info ||| "
              << "sending shutdown message to publisher" << std::endl;
    std::shared_ptr<vsomeip::message> ready_req = vsomeip::runtime::get()->create_request();
    ready_req->set_service(service_id_);
    ready_req->set_instance(instance_id_);
    ready_req->set_method(shutdown_method_id_);
    appl_->send(ready_req);

    std::cout << ">>>> info ||| "
              << "# packets received " << packet_count_ << ", # messages received "
              << message_counter_ << std::endl;

    exit();
  }

  void on_subscription_status_change(const vsomeip::service_t service,
                                     const vsomeip::instance_t instance,
                                     const vsomeip::eventgroup_t eventgroup,
                                     const vsomeip::eventgroup_t event_id, const uint16_t subcode) {
    is_subscribed_ = service == service_id_ && instance == instance_id_ &&
                     eventgroup == eventgroup_id_ && event_id == event_id_ &&
                     subcode == SubscriptionReturnCode::ACCPETED;
    std::cout << ">>>> info ||| "
              << (is_subscribed_ ? "subscribed to eventgroup" : "not subscribed to eventgroup")
              << std::endl;
    cv_.notify_all();
  }

  bool on_subscription_change(const vsomeip::client_t client, const vsomeip::uid_t uid,
                              const vsomeip::gid_t gid, const bool stats) {
    std::cout << ">>>> info ||| " << (stats ? "client/uid/gid => true" : "client/uid/gid => false")
              << std::endl;
    return stats;
  }



 private:
  std::shared_ptr<vsomeip::application> appl_;
  std::uint16_t service_id_ , instance_id_;
  std::uint16_t eventgroup_id_ , event_id_ ;
  std::uint16_t ready_method_id_;
  std::uint16_t shutdown_method_id_ = 0x8888;
  std::thread someip_thread_;
  std::atomic<bool> stop_token_{false};
  std::atomic<bool> is_registered_{false};
  std::atomic<bool> is_available_{false};
  std::atomic<bool> is_subscribed_{false};
  std::atomic<bool> is_someip_running_{false};
  std::atomic<bool> start_clock_{false};
  std::size_t message_counter_{0};
  std::size_t packet_count_{0};
  std::mutex mutex_;
  std::condition_variable cv_;
  std::chrono::system_clock::time_point first_ts_, last_ts_;
  std::vector<std::chrono::microseconds> latencies;
  int last_id_{0};
};


/**************************************publish**********************/


class pubVsomeIP {
 public:
  pubVsomeIP(std ::string topic){
      application_ = (vsomeip::runtime::get()->create_application("service-sample"));
      if (topic.compare("Tracer") == 0){
        service_id_ = 0x1234, instance_id_ = 0x5678;
      eventgroup_id_ = 0x4455, event_id_ = 0x8777;
      ready_method_id_ = 0x7777;
      }else{
        service_id_ = 0x0248, instance_id_ = 0x5422;
      eventgroup_id_ = 0x4455, event_id_ = 0x8777;
      ready_method_id_ = 0x1421;
        
      }
      if (topic.compare("Benchi") == 0){
        service_id_ = 0x1245, instance_id_ = 0x5645;
      eventgroup_id_ = 0x4445, event_id_ = 0x8745;
      ready_method_id_ = 0x7745;
      }
      
  }  

  ~pubVsomeIP() { exit(); }

  bool init() {
    if (!application_->init()) {
      std::cout << ">>>> error ||| "
                << "application initializtion failed" << std::endl;
      return false;
    }

    application_->register_state_handler([this](vsomeip::state_type_e e) { this->on_state(e); });

    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(eventgroup_id_);
    application_->offer_event(service_id_, instance_id_, event_id_, its_groups,
                              vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds::zero(),
                              false, true, nullptr, vsomeip::reliability_type_e::RT_UNRELIABLE);

    application_->register_message_handler(service_id_, instance_id_, ready_method_id_,
                                           [this](const auto &msg) { this->on_ready(msg); });

    application_->register_message_handler(service_id_, instance_id_, shutdown_method_id_,
                                           [this](const auto &msg) { this->on_shutdown(msg); });

    return true;
  }

  void start() {
    someip_thread_ = std::thread([this]() { application_->start(); });
    is_someip_running_ = true;
  }

  void run(const std::string message, std::chrono::milliseconds spacing) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() { return is_registered_.load(); });
    offer();
    cv_.wait(lk, [this]() { return is_listening_.load(); });
    //send(message, spacing);
    std::shared_ptr< vsomeip::payload > payload = vsomeip::runtime::get()->create_payload();
  // Create a payload which will be sent to the service      
   //std::string str(newme->data);
   std::vector<vsomeip::byte_t> pl_data(std::begin(message), std::end(message));
   std::cout << "sending data" << message;
   payload->set_data(pl_data);
   application_->notify(service_id_, instance_id_, event_id_, payload);
  }

  void offer() {
    std::cout << ">>>> info ||| "
              << "offering services" << std::endl;
    application_->offer_service(service_id_, instance_id_);
  }



  bool exit() {
    std::cout << "number of packets sent " << n_packets_sent_ << std::endl;
    application_->clear_all_handler();
    application_->stop_offer_service(service_id_, instance_id_);
    application_->stop();
    if (someip_thread_.joinable()) {
      someip_thread_.join();
      is_someip_running_ = false;
    }
    return true;
  }

  void on_state(vsomeip::state_type_e e) {
    is_registered_ = e == vsomeip::state_type_e::ST_REGISTERED;
    std::cout << ">>>> info ||| "
              << "service is " << (is_registered_ ? "registered" : "de-registered") << std::endl;
    cv_.notify_one();
  }

  void on_ready(const std::shared_ptr<vsomeip::message> &msg) {
    std::cout << ">>>> info ||| "
              << "subVsomeIP is ready to get messages" << std::endl;
    is_listening_ = true;
    cv_.notify_one();
  }

  void on_shutdown(const std::shared_ptr<vsomeip::message> &msg) {
    std::cout << ">>>> info ||| "
              << "shutdown message has been received" << std::endl;
    is_ending_ = true;
    cv_.notify_all();
    exit();
  }

 private:
  std::shared_ptr<vsomeip::application> application_;
  std::uint16_t service_id_ , instance_id_ ;
  std::uint16_t  eventgroup_id_ , event_id_ ;

  std::uint16_t ready_method_id_;
  std::uint16_t shutdown_method_id_ = 0x8888;
  std::thread someip_thread_;
  std::atomic<bool> is_reliable_{true};
  std::atomic<bool> is_registered_{false};
  std::atomic<bool> is_someip_running_{false};
  std::atomic<bool> is_listening_{false};
  std::atomic<bool> is_ending_{false};
  std::size_t n_packets_sent_{0};
  std::mutex mutex_;
  std::condition_variable cv_;
  std::vector<std::chrono::microseconds> delays_;
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif
struct framwork;
  void vsmip_operation_initialize(struct framwork *frame);
  #ifdef __cplusplus
}
#endif