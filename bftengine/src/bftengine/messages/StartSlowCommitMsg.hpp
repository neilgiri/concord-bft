// Concord
//
// Copyright (c) 2018 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License").  You may not use this product except in
// compliance with the Apache 2.0 License.
//
// This product may include a number of subcomponents with separate copyright notices and license terms. Your use of
// these subcomponents is subject to the terms and conditions of the subcomponent's license, as noted in the LICENSE
// file.

#pragma once

#include <locale>
#include <string>
#include "MessageBase.hpp"

namespace bftEngine {
namespace impl {

class StartSlowCommitMsg : public MessageBase {
 public:
  StartSlowCommitMsg(ReplicaId senderId, ViewNum v, SeqNum s, const std::string& spanContext = "");

  ViewNum viewNumber() const { return b()->viewNum; }

  SeqNum seqNumber() const { return b()->seqNum; }

  std::string spanContext() const override {
    return std::string(body() + sizeof(StartSlowCommitMsgHeader), spanContextSize());
  }

  void validate(const ReplicasInfo&) const override;

 protected:
#pragma pack(push, 1)
  struct StartSlowCommitMsgHeader {
    MessageBase::Header header;
    ViewNum viewNum;
    SeqNum seqNum;
  };
#pragma pack(pop)
  static_assert(sizeof(StartSlowCommitMsgHeader) == (6 + 8 + 8), "StartSlowCommitMsgHeader is 16B");

  StartSlowCommitMsgHeader* b() const { return (StartSlowCommitMsgHeader*)msgBody_; }
};

}  // namespace impl
}  // namespace bftEngine
