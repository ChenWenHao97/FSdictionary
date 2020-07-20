// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: echo_service.proto

#ifndef PROTOBUF_echo_5fservice_2eproto__INCLUDED
#define PROTOBUF_echo_5fservice_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/service.h>
// @@protoc_insertion_point(includes)

namespace fs {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_echo_5fservice_2eproto();
void protobuf_AssignDesc_echo_5fservice_2eproto();
void protobuf_ShutdownFile_echo_5fservice_2eproto();

class EchoRequest;
class EchoResponse;

// ===================================================================

class EchoRequest : public ::google::protobuf::Message {
 public:
  EchoRequest();
  virtual ~EchoRequest();
  
  EchoRequest(const EchoRequest& from);
  
  inline EchoRequest& operator=(const EchoRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const EchoRequest& default_instance();
  
  void Swap(EchoRequest* other);
  
  // implements Message ----------------------------------------------
  
  EchoRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EchoRequest& from);
  void MergeFrom(const EchoRequest& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string message = 1;
  inline bool has_message() const;
  inline void clear_message();
  static const int kMessageFieldNumber = 1;
  inline const ::std::string& message() const;
  inline void set_message(const ::std::string& value);
  inline void set_message(const char* value);
  inline void set_message(const char* value, size_t size);
  inline ::std::string* mutable_message();
  inline ::std::string* release_message();
  
  // @@protoc_insertion_point(class_scope:fs.EchoRequest)
 private:
  inline void set_has_message();
  inline void clear_has_message();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* message_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_echo_5fservice_2eproto();
  friend void protobuf_AssignDesc_echo_5fservice_2eproto();
  friend void protobuf_ShutdownFile_echo_5fservice_2eproto();
  
  void InitAsDefaultInstance();
  static EchoRequest* default_instance_;
};
// -------------------------------------------------------------------

class EchoResponse : public ::google::protobuf::Message {
 public:
  EchoResponse();
  virtual ~EchoResponse();
  
  EchoResponse(const EchoResponse& from);
  
  inline EchoResponse& operator=(const EchoResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const EchoResponse& default_instance();
  
  void Swap(EchoResponse* other);
  
  // implements Message ----------------------------------------------
  
  EchoResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EchoResponse& from);
  void MergeFrom(const EchoResponse& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string message = 1;
  inline bool has_message() const;
  inline void clear_message();
  static const int kMessageFieldNumber = 1;
  inline const ::std::string& message() const;
  inline void set_message(const ::std::string& value);
  inline void set_message(const char* value);
  inline void set_message(const char* value, size_t size);
  inline ::std::string* mutable_message();
  inline ::std::string* release_message();
  
  // @@protoc_insertion_point(class_scope:fs.EchoResponse)
 private:
  inline void set_has_message();
  inline void clear_has_message();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* message_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_echo_5fservice_2eproto();
  friend void protobuf_AssignDesc_echo_5fservice_2eproto();
  friend void protobuf_ShutdownFile_echo_5fservice_2eproto();
  
  void InitAsDefaultInstance();
  static EchoResponse* default_instance_;
};
// ===================================================================

class EchoServer_Stub;

class EchoServer : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline EchoServer() {};
 public:
  virtual ~EchoServer();
  
  typedef EchoServer_Stub Stub;
  
  static const ::google::protobuf::ServiceDescriptor* descriptor();
  
  virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::fs::EchoRequest* request,
                       ::fs::EchoResponse* response,
                       ::google::protobuf::Closure* done);
  
  // implements Service ----------------------------------------------
  
  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EchoServer);
};

class EchoServer_Stub : public EchoServer {
 public:
  EchoServer_Stub(::google::protobuf::RpcChannel* channel);
  EchoServer_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~EchoServer_Stub();
  
  inline ::google::protobuf::RpcChannel* channel() { return channel_; }
  
  // implements EchoServer ------------------------------------------
  
  void Echo(::google::protobuf::RpcController* controller,
                       const ::fs::EchoRequest* request,
                       ::fs::EchoResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EchoServer_Stub);
};


// ===================================================================


// ===================================================================

// EchoRequest

// required string message = 1;
inline bool EchoRequest::has_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EchoRequest::set_has_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EchoRequest::clear_has_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EchoRequest::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& EchoRequest::message() const {
  return *message_;
}
inline void EchoRequest::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void EchoRequest::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void EchoRequest::set_message(const char* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* EchoRequest::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* EchoRequest::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// EchoResponse

// required string message = 1;
inline bool EchoResponse::has_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EchoResponse::set_has_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EchoResponse::clear_has_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EchoResponse::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& EchoResponse::message() const {
  return *message_;
}
inline void EchoResponse::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void EchoResponse::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void EchoResponse::set_message(const char* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* EchoResponse::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* EchoResponse::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace fs

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_echo_5fservice_2eproto__INCLUDED
